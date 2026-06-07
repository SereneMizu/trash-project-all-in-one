package com.sipc.trash.pojo.domain.DO;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableField;
import com.baomidou.mybatisplus.annotation.TableId;
import com.fasterxml.jackson.annotation.JsonFormat;
import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.Data;

import java.util.Date;

@Data
public class EventDetailDo {
    @JsonProperty("event_id")
    private Integer eventId;
    @JsonProperty("event_name")
    private String eventName;
    @JsonProperty("bin_id")
    private Integer binId;
    @JsonProperty("bin_name")
    private String binName;
    @JsonProperty("cluster_id")
    private Integer clusterId;
    @JsonProperty("cluster_name")
    private String clusterName;
    private String status;
    @TableField("`trigger`")
    @JsonProperty("trigger")
    private String trigger;
    @TableField("event_time")
    @JsonProperty("event_time")
    private String eventTime;
}
