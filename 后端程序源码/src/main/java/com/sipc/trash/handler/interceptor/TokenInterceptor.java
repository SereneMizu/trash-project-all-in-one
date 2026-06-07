package com.sipc.trash.handler.interceptor;


import com.fasterxml.jackson.databind.ObjectMapper;
import com.sipc.trash.handler.token.TokenHandler;
import com.sipc.trash.pojo.CommonResult;
import com.sipc.trash.util.JwtUtils;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import org.springframework.web.servlet.HandlerInterceptor;
import org.springframework.web.servlet.ModelAndView;

public class TokenInterceptor implements HandlerInterceptor {
    @Override
    public boolean preHandle(HttpServletRequest request, HttpServletResponse response, Object handler) throws Exception {
        String token = request.getHeader("Authorization");
        if (token == null || token.isEmpty() || !JwtUtils.verify(token)) {
            response.setCharacterEncoding("UTF-8");
            response.setContentType("application/json; charset=utf-8");
            ObjectMapper objectMapper = new ObjectMapper();
            if (token == null || token.isEmpty()) {
                response.getWriter().println(objectMapper.writeValueAsString(CommonResult.fail("token cannot be empty!")));
            } else {
                response.getWriter().println(objectMapper.writeValueAsString(CommonResult.fail("incorrect token!")));
            }
            return false;
        }
        TokenHandler.setTokenModelThreadLocal(JwtUtils.getTokenModelByToken(token));
        return true;
    }

    @Override
    public void postHandle(HttpServletRequest request, HttpServletResponse response, Object handler, ModelAndView modelAndView) throws Exception {
        HandlerInterceptor.super.postHandle(request, response, handler, modelAndView);
    }

    @Override
    public void afterCompletion(HttpServletRequest request, HttpServletResponse response, Object handler, Exception ex) {
        TokenHandler.remove();
    }
}
