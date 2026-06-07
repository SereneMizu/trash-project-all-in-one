package com.sipc.trash.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.sipc.trash.pojo.domain.DO.EventDetailDo;
import com.sipc.trash.pojo.domain.PO.Event;
import lombok.Data;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;
import org.apache.ibatis.annotations.Select;

import java.util.Date;
import java.util.List;

@Mapper
public interface EventMapper extends BaseMapper<Event> {
    List<EventDetailDo> selectEventDetail(@Param("clusterId") Integer clusterId, @Param("binId") Integer binId,
                                          @Param("startTime") String startTime, @Param("endTime") String endTime,
                                          @Param("status") String status, @Param("trigger") String trigger);
}
