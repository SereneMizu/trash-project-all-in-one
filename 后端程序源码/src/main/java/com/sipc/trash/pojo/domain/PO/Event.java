package com.sipc.trash.pojo.domain.PO;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableField;
import com.baomidou.mybatisplus.annotation.TableId;
import com.fasterxml.jackson.annotation.JsonFormat;
import lombok.Data;

import java.util.Date;

@Data
public class Event {
    @TableId(value = "event_id", type = IdType.AUTO)
    private Integer eventId;
    private Integer binId;
    private String eventName;
    private String status;
    @TableField("`trigger`")
    private String trigger;
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss", timezone = "GMT+8")
    private Date eventTime;
}
