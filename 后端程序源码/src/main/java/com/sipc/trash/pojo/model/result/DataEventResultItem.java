package com.sipc.trash.pojo.model.result;

import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.Data;

import java.util.Date;

@Data
public class DataEventResultItem {
    @JsonProperty("event_id")
    private int eventId;
    @JsonProperty("bin_id")
    private int binId;
    private String status;
    private String trigger;
    @JsonProperty("event_time")
    private Date eventTime;
}
