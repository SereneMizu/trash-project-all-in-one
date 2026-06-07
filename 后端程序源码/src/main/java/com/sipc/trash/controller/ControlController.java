package com.sipc.trash.controller;

import com.sipc.trash.pojo.CommonResult;
import com.sipc.trash.pojo.model.request.UserLoginRequest;
import com.sipc.trash.pojo.model.request.UserRegisterRequest;
import com.sipc.trash.pojo.model.result.AuthResult;
import com.sipc.trash.service.ControlService;
import com.sipc.trash.service.UserService;
import lombok.AllArgsConstructor;
import org.springframework.web.bind.annotation.*;

@RestController
@AllArgsConstructor
@RequestMapping("/control")
public class ControlController {
    private ControlService controlService;

    @GetMapping("/open/{bin_id}")
    public CommonResult<String> open(@PathVariable("bin_id") Integer binId) {
        return controlService.open(binId);
    }
}
