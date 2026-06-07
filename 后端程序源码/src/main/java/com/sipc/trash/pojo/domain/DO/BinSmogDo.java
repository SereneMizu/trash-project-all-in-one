package com.sipc.trash.pojo.domain.DO;

import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.Data;

import java.util.Date;

@Data
public class BinSmogDo {
    private Integer value;
    private Date date;
}
