package com.sipc.trash.pojo.domain.DO;

import com.baomidou.mybatisplus.annotation.TableField;
import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.Data;

import java.util.Date;
import java.util.List;

@Data
public class ClusterRubbishDo {
    private Date date;
    @JsonProperty("residual_waste_count")
    private Integer residualWasteCount;
    @JsonProperty("recyclable_count")
    private Integer recyclableCount;
    @JsonProperty("food_waste_count")
    private Integer foodWasteCount;
    @JsonProperty("hazardous_waste_count")
    private Integer hazardousWasteCount;
}
