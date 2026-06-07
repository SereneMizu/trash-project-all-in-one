package com.sipc.trash.pojo.domain.DO;

import com.baomidou.mybatisplus.annotation.TableField;
import lombok.Data;

import java.util.Date;

@Data
public class ClusterLidDo {
    private Integer count;
    private Date date;
}
