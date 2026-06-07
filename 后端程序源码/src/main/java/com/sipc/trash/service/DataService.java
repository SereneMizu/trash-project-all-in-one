package com.sipc.trash.service;

import com.sipc.trash.pojo.CommonResult;
import com.sipc.trash.pojo.domain.DO.EventDetailDo;
import com.sipc.trash.pojo.model.request.DataEventRequest;
import com.sipc.trash.pojo.model.result.*;

import java.text.ParseException;
import java.util.List;

public interface DataService {
    CommonResult<List<DataClusterResultItem>> getClusterList();

    CommonResult<DataClusterLidResult> getClusterLid(Integer clusterId);

    CommonResult<DataClusterRubbishResult> getClusterRubbish(Integer clusterId);

    CommonResult<List<DataClusterBinResultItem>> getClusterBinList(Integer clusterId);

    CommonResult<DataClusterBinMethaneResult> getClusterBinMethane(Integer binId);

    CommonResult<DataClusterBinSmogResult> getClusterBinSmog(Integer binId);

    CommonResult<List<EventDetailDo>> getEventList(DataEventRequest request);

    CommonResult<String> deleteEvent(Integer eventId);
}
