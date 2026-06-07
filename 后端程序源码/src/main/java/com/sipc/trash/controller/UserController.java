package com.sipc.trash.controller;

import com.sipc.trash.pojo.CommonResult;
import com.sipc.trash.pojo.model.request.UserLoginRequest;
import com.sipc.trash.pojo.model.request.UserRegisterRequest;
import com.sipc.trash.pojo.model.result.AuthResult;
import com.sipc.trash.service.UserService;
import lombok.AllArgsConstructor;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
@AllArgsConstructor
@RequestMapping("/user")
public class UserController {
    private UserService userService;

    @PostMapping("/login")
    public CommonResult<AuthResult> login(@RequestBody UserLoginRequest userLoginRequest) {
        return userService.login(userLoginRequest);
    }

    @PostMapping("/register")
    public CommonResult<String> register(@RequestBody UserRegisterRequest userRegisterRequest) {
        return userService.register(userRegisterRequest);
    }
}
