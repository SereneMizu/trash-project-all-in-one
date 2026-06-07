package com.sipc.trash.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.sipc.trash.pojo.domain.PO.User;
import org.apache.ibatis.annotations.Mapper;

@Mapper
public interface UserMapper extends BaseMapper<User> {
}
