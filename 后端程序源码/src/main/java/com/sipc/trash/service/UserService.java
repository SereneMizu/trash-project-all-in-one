package com.sipc.trash.service;

import com.sipc.trash.pojo.CommonResult;
import com.sipc.trash.pojo.domain.PO.User;
import com.sipc.trash.pojo.model.request.UserLoginRequest;
import com.sipc.trash.pojo.model.request.UserRegisterRequest;
import com.sipc.trash.pojo.model.result.AuthResult;

public interface UserService {
    CommonResult<AuthResult> login(UserLoginRequest userLoginRequest);
    CommonResult<String> register(UserRegisterRequest userRegisterRequest);
}
