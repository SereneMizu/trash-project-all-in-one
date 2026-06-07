package com.sipc.trash.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.sipc.trash.pojo.domain.DO.BinMethaneDo;
import com.sipc.trash.pojo.domain.DO.BinSmogDo;
import com.sipc.trash.pojo.domain.DO.ClusterLidDo;
import com.sipc.trash.pojo.domain.DO.ClusterRubbishDo;
import com.sipc.trash.pojo.domain.PO.Bin;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

import java.util.List;

@Mapper
public interface BinMapper extends BaseMapper<Bin> {
    List<ClusterLidDo> getClusterLid(@Param("clusterId") Integer clusterId);

    List<ClusterRubbishDo> getClusterRubbish(@Param("clusterId") Integer clusterId);

    List<BinMethaneDo> getBinMethane(@Param("binId") Integer binId);

    List<BinSmogDo> getBinSmog(@Param("binId") Integer binId);
}
