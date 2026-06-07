package com.sipc.trash.pojo.model.request;

import lombok.Data;

@Data
public class UserRegisterRequest {
    private String account;
    private String password;
    private String username;
}
