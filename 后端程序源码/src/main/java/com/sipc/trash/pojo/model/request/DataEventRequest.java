package com.sipc.trash.pojo.model.request;


import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.Data;

@Data
public class DataEventRequest {
    @JsonProperty("bin_id")
    private Integer BinId;
    @JsonProperty("cluster_id")
    private Integer ClusterId;
    @JsonProperty("end_time")
    private String endTime;
    @JsonProperty("start_time")
    private String startTime;
    private String status;
    private String trigger;
}
