package com.sipc.trash.pojo.domain.PO;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import lombok.Data;

import java.util.Date;

@Data
public class Bin {
    @TableId(value = "bin_id", type = IdType.AUTO)
    private Integer binId;
    private Integer clusterId;
    private String binName;
    private String boardId;
    private Integer posX;
    private Integer posY;
}
