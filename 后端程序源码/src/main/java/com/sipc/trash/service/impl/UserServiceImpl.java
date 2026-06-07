package com.sipc.trash.service.impl;

import com.baomidou.mybatisplus.core.conditions.query.QueryWrapper;
import com.sipc.trash.mapper.UserMapper;
import com.sipc.trash.pojo.CommonResult;
import com.sipc.trash.pojo.domain.PO.User;
import com.sipc.trash.pojo.model.request.UserLoginRequest;
import com.sipc.trash.pojo.model.request.UserRegisterRequest;
import com.sipc.trash.pojo.model.result.AuthResult;
import com.sipc.trash.service.UserService;
import com.sipc.trash.util.JwtUtils;
import com.sipc.trash.util.MD5Utils;
import lombok.AllArgsConstructor;
import org.springframework.stereotype.Service;

@Service
@AllArgsConstructor
public class UserServiceImpl implements UserService {
    private UserMapper userMapper;

    @Override
    public CommonResult<AuthResult> login(UserLoginRequest userLoginRequest) {
        QueryWrapper<User> queryWrapper = new QueryWrapper<>();
        queryWrapper.eq("account", userLoginRequest.getAccount());
        queryWrapper.eq("password", MD5Utils.encrypt(userLoginRequest.getPassword()));
        User user = userMapper.selectOne(queryWrapper);
        if (user == null) {
            return CommonResult.fail("用户名或密码错误");
        }
        AuthResult authResult = new AuthResult();
        authResult.setToken(JwtUtils.sign(user));
        return CommonResult.success("成功", authResult);
    }

    public CommonResult<String> register(UserRegisterRequest userRegisterRequest) {
        QueryWrapper<User> queryWrapper = new QueryWrapper<>();
        queryWrapper.eq("account", userRegisterRequest.getAccount());
        User existingUser = userMapper.selectOne(queryWrapper);
        if (existingUser != null) {
            return CommonResult.fail("用户已存在");
        }
        User user = new User();
        user.setAccount(userRegisterRequest.getAccount());
        user.setPassword(MD5Utils.encrypt(userRegisterRequest.getPassword()));
        user.setUserName(userRegisterRequest.getUsername());
        userMapper.insert(user);
        return CommonResult.success("成功");
    }

}
