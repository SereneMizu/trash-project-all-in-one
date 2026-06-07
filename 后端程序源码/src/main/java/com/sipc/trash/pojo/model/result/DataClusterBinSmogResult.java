package com.sipc.trash.pojo.model.result;

import lombok.Data;

import java.util.List;

@Data
public class DataClusterBinSmogResult {
    private List<String> date;
    private List<Integer> value;
}
