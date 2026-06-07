package com.sipc.trash.pojo.model.result;

import lombok.Data;

import java.util.List;

@Data
public class DataClusterLidResult {
    private List<String> date;
    private List<Integer> count;
}
