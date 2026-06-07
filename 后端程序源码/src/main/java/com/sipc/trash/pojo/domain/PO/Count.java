package com.sipc.trash.pojo.domain.PO;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import lombok.Data;

import java.util.Date;

@Data
public class Count {
    @TableId(value = "count_id", type = IdType.AUTO)
    private Integer countId;
    private Integer binId;
    private Integer residualWasteCount;
    private Integer recyclableCount;
    private Integer foodWasteCount;
    private Integer hazardousWasteCount;
    private Integer lidCount;
    private Date date;
}
