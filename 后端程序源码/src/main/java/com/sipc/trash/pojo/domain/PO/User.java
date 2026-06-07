package com.sipc.trash.pojo.domain.PO;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import lombok.Data;

@Data
public class User {
    @TableId(value = "user_id", type = IdType.AUTO)
    private Integer UserId;
    private String userName;
    private String account;
    private String password;
}
