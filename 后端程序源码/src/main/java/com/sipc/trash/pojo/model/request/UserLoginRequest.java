package com.sipc.trash.pojo.model.request;

import lombok.Data;

@Data
public class UserLoginRequest {
    private String account;
    private String password;
}
