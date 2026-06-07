package com.sipc.trash.pojo.domain.PO;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import lombok.Data;

@Data
public class Cluster {
    @TableId(value = "cluster_id", type = IdType.AUTO)
    private Integer clusterId;
    private String clusterName;
}
