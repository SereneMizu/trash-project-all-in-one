package com.sipc.trash.pojo.model.result;

import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.Data;

import java.util.List;

@Data
public class DataClusterRubbishResult {
    private List<String> date;
    @JsonProperty("residual_waste_count")
    private List<Integer> residualWasteCount;
    @JsonProperty("recyclable_count")
    private List<Integer> recyclableCount;
    @JsonProperty("food_waste_count")
    private List<Integer> foodWasteCount;
    @JsonProperty("hazardous_waste_count")
    private List<Integer> hazardousWasteCount;
}
