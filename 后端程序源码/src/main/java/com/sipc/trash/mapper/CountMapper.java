package com.sipc.trash.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.sipc.trash.pojo.domain.PO.Count;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

@Mapper
public interface CountMapper extends BaseMapper<Count> {
    Count selectByDateAndId(@Param("binId") Integer id);

    void insertByBinId(@Param("binId") Integer binId);

    void updateLidCount(@Param("binId") Integer binId);

    void updateResidualWasteCount(@Param("binId") Integer binId);

    void updateRecyclableCount(@Param("binId") Integer binId);

    void updateFoodWasteCount(@Param("binId") Integer binId);

    void updateHazardousWasteCount(@Param("binId") Integer binId);

}
