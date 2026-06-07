package com.sipc.trash.service.impl;

import com.baomidou.mybatisplus.core.conditions.query.QueryWrapper;
import com.sipc.trash.mapper.BinMapper;
import com.sipc.trash.mapper.ClusterMapper;
import com.sipc.trash.mapper.EventMapper;
import com.sipc.trash.pojo.CommonResult;
import com.sipc.trash.pojo.domain.DO.*;
import com.sipc.trash.pojo.domain.PO.Bin;
import com.sipc.trash.pojo.domain.PO.Cluster;
import com.sipc.trash.pojo.model.request.DataEventRequest;
import com.sipc.trash.pojo.model.result.*;
import com.sipc.trash.service.DataService;
import com.sipc.trash.util.StringUtils;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.extern.slf4j.Slf4j;
import org.springframework.stereotype.Service;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

@Slf4j
@Service
@AllArgsConstructor
public class DataServiceImpl implements DataService {
    private ClusterMapper clusterMapper;
    private BinMapper binMapper;
    private EventMapper eventMapper;

    @Override
    public CommonResult<List<DataClusterResultItem>> getClusterList() {
        List<Cluster> clusterList = clusterMapper.selectList(null);
        List<DataClusterResultItem> dataClusterResultItemList = new ArrayList<>();
        for (Cluster cluster : clusterList) {
            DataClusterResultItem dataClusterResultItem = new DataClusterResultItem();
            dataClusterResultItem.setClusterId(cluster.getClusterId());
            dataClusterResultItem.setClusterName(cluster.getClusterName());
            dataClusterResultItemList.add(dataClusterResultItem);
        }
        return CommonResult.success(dataClusterResultItemList);
    }

    @Override
    public CommonResult<DataClusterLidResult> getClusterLid(Integer clusterId) {
        List<ClusterLidDo> lidDos = binMapper.getClusterLid(clusterId);
        List<Integer> count = new ArrayList<>();
        List<String> date = new ArrayList<>();
        for (ClusterLidDo lidDo : lidDos) {
            count.add(lidDo.getCount());
            date.add(new SimpleDateFormat("MM.dd").format(lidDo.getDate()));
        }
        DataClusterLidResult dataClusterLidResult = new DataClusterLidResult();
        dataClusterLidResult.setCount(count);
        dataClusterLidResult.setDate(date);
        return CommonResult.success(dataClusterLidResult);
    }

    @Override
    public CommonResult<DataClusterRubbishResult> getClusterRubbish(Integer clusterId) {
//        return null;
        List<ClusterRubbishDo> rubbishDos = binMapper.getClusterRubbish(clusterId);
        List<Integer> count1 = new ArrayList<>();
        List<Integer> count2 = new ArrayList<>();
        List<Integer> count3 = new ArrayList<>();
        List<Integer> count4 = new ArrayList<>();
        List<String> date = new ArrayList<>();
        for (ClusterRubbishDo rubbishDo : rubbishDos) {
            count1.add(rubbishDo.getRecyclableCount());
            count2.add(rubbishDo.getFoodWasteCount());
            count3.add(rubbishDo.getHazardousWasteCount());
            count4.add(rubbishDo.getResidualWasteCount());
            date.add(new SimpleDateFormat("MM.dd").format(rubbishDo.getDate()));
        }
        DataClusterRubbishResult dataClusterRubbishResult = new DataClusterRubbishResult();
        dataClusterRubbishResult.setRecyclableCount(count1);
        dataClusterRubbishResult.setFoodWasteCount(count2);
        dataClusterRubbishResult.setHazardousWasteCount(count3);
        dataClusterRubbishResult.setResidualWasteCount(count4);
        dataClusterRubbishResult.setDate(date);
        return CommonResult.success(dataClusterRubbishResult);
    }

    @Override
    public CommonResult<List<DataClusterBinResultItem>> getClusterBinList(Integer clusterId) {
        QueryWrapper<Cluster> clusterQueryWrapper = new QueryWrapper<>();
        clusterQueryWrapper.eq("cluster_id", clusterId);
        List<Cluster> clusterList = clusterMapper.selectList(clusterQueryWrapper);
        if (clusterList == null || clusterList.isEmpty()) {
            return CommonResult.fail("没有这个集群");
        }
        QueryWrapper<Bin> binQueryWrapper = new QueryWrapper<>();
        binQueryWrapper.eq("cluster_id", clusterId);
        List<Bin> binList = binMapper.selectList(binQueryWrapper);
        List<DataClusterBinResultItem> dataClusterBinResultItemList = new ArrayList<>();
        for (Bin bin : binList) {
            DataClusterBinResultItem dataClusterBinResultItem = new DataClusterBinResultItem();
            dataClusterBinResultItem.setBinId(bin.getBinId());
            dataClusterBinResultItem.setBinName(bin.getBinName());
            dataClusterBinResultItemList.add(dataClusterBinResultItem);
        }

        return CommonResult.success(dataClusterBinResultItemList);
    }

    @Override
    public CommonResult<DataClusterBinMethaneResult> getClusterBinMethane(Integer binId) {
        List<BinMethaneDo> methaneDos = binMapper.getBinMethane(binId);
        List<Integer> values = new ArrayList<>();
        List<String> date = new ArrayList<>();
        for (BinMethaneDo methaneDo : methaneDos) {
            values.add(methaneDo.getValue());
            SimpleDateFormat formatter = new SimpleDateFormat("MM-dd");
            String strDate = formatter.format(methaneDo.getDate());
            date.add(strDate);
        }
        DataClusterBinMethaneResult dataClusterBinMethaneResult = new DataClusterBinMethaneResult();
        dataClusterBinMethaneResult.setValue(values);
        dataClusterBinMethaneResult.setDate(date);
        return CommonResult.success(dataClusterBinMethaneResult);
    }

    @Override
    public CommonResult<DataClusterBinSmogResult> getClusterBinSmog(Integer binId) {
        List<BinSmogDo> smogDos = binMapper.getBinSmog(binId);
        List<Integer> values = new ArrayList<>();
        List<String> date = new ArrayList<>();
        for (BinSmogDo smogDo : smogDos) {
            values.add(smogDo.getValue());
            SimpleDateFormat formatter = new SimpleDateFormat("MM-dd");
            String strDate = formatter.format(smogDo.getDate());
            date.add(strDate);
        }
        DataClusterBinSmogResult dataClusterBinSmogResult = new DataClusterBinSmogResult();
        dataClusterBinSmogResult.setValue(values);
        dataClusterBinSmogResult.setDate(date);
        return CommonResult.success(dataClusterBinSmogResult);
    }

    @Override
    public CommonResult<List<EventDetailDo>> getEventList(DataEventRequest request) {

        List<EventDetailDo> eventDetailDos = eventMapper.selectEventDetail(request.getClusterId(),
                request.getBinId(), request.getStartTime(),
                request.getEndTime(), request.getStatus(), request.getTrigger());
        return CommonResult.success(eventDetailDos);

    }

    public CommonResult<String> deleteEvent(Integer eventId) {
        eventMapper.deleteById(eventId);
        return CommonResult.success();
    }
}
