package com.sipc.trash.handler.exception;


import cn.hutool.json.JSONArray;
import cn.hutool.json.JSONObject;
import com.sipc.trash.pojo.CommonResult;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.http.converter.HttpMessageNotReadableException;
import org.springframework.web.bind.annotation.ControllerAdvice;
import org.springframework.web.bind.annotation.ExceptionHandler;
import org.springframework.web.bind.annotation.ResponseStatus;
import org.springframework.web.servlet.NoHandlerFoundException;

import java.io.PrintWriter;
import java.io.StringWriter;
import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.util.Date;


@Slf4j
@ControllerAdvice
public class GlobalExceptionHandler {
    @Value("${notification.feishu-bot:false}")
    private boolean feishuBotEnabled;
    private static long lastTime = 0;

    @ExceptionHandler(HttpMessageNotReadableException.class)
    @ResponseStatus(HttpStatus.BAD_REQUEST)
    public ResponseEntity<Object> handleHttpMessageNotReadableException(HttpMessageNotReadableException ex) {
        log.error("http message not readable: {}", ex.getMessage());
        return new ResponseEntity<>(CommonResult.fail("数据解析异常"), HttpStatus.BAD_REQUEST);
    }

    @ExceptionHandler(NoHandlerFoundException.class)
    @ResponseStatus(HttpStatus.BAD_REQUEST)
    public ResponseEntity<Object> handleNoHandlerFoundException(NoHandlerFoundException ex) {
        log.error("no handler found: {}", ex.getMessage());
        return new ResponseEntity<>(CommonResult.fail("无效的请求"), HttpStatus.BAD_REQUEST);
    }

    @ExceptionHandler(Exception.class)
    @ResponseStatus(HttpStatus.INTERNAL_SERVER_ERROR)
    public CommonResult<Object> handleUncaughtException(Exception e) {
        log.error("Uncaught Exception:\n{}", e.getMessage(), e);
        if (feishuBotEnabled) {
            sendExceptionFeishuNotification(e);
        }
        return CommonResult.fail(e.getMessage());
    }

    public void sendExceptionFeishuNotification(Exception exception) {
        // 至少间隔十秒
        long currentTime = System.currentTimeMillis();

        if (currentTime - lastTime < 1000 * 2) {
            lastTime = currentTime;
            log.info("间隔太短，取消发送");
            return;
        }
        lastTime = currentTime;
        log.info("Send Feishu Notification");
        String url = "https://open.feishu.cn/open-apis/bot/v2/hook/b39b9070-1662-4512-884d-6b0ce6833a11";

        //构建json
        JSONObject json = new JSONObject();
        json.set("msg_type", "text").set("content", new JSONObject().set("text", exception.getMessage()));
        HttpClient client = HttpClient.newHttpClient();
        HttpRequest request = HttpRequest.newBuilder().uri(URI.create(url)).header("Content-Type", "application/json").POST(HttpRequest.BodyPublishers.ofString(json.toString())).build();

        try {
//            System.out.println(client.send(request, HttpResponse.BodyHandlers.ofString()).body());
            client.send(request, HttpResponse.BodyHandlers.ofString());
            log.info("Send Feishu Notification: Success");
        } catch (Exception e) {
            log.info("Send Feishu Notification: Failed");
        }

    }
}
