package com.sipc.trash.pojo.domain.PO;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import lombok.Data;

import java.util.Date;

@Data
public class Value {
    @TableId(value = "value_id", type = IdType.AUTO)
    private Integer valueId;
    private Integer binId;
    private Float smogValue;
    private Float methaneValue;
    private Date date;
}
