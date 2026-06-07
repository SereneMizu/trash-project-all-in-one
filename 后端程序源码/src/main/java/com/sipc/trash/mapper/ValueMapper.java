package com.sipc.trash.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.sipc.trash.pojo.domain.PO.Value;
import org.apache.ibatis.annotations.Mapper;

@Mapper
public interface ValueMapper extends BaseMapper<Value> {
    void deleteOldData();
}
