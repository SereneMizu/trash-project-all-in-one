package com.sipc.trash.pojo.model.result;

import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.Data;

@Data
public class DataClusterResultItem {
    @JsonProperty("cluster_id")
    private Integer clusterId;
    @JsonProperty("cluster_name")
    private String clusterName;
}
