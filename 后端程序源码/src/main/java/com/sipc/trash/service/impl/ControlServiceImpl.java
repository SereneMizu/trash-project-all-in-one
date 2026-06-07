package com.sipc.trash.service.impl;

import com.baomidou.mybatisplus.core.conditions.query.QueryWrapper;
import com.sipc.trash.config.MqttConfig;
import com.sipc.trash.mapper.BinMapper;
import com.sipc.trash.pojo.CommonResult;
import com.sipc.trash.pojo.domain.PO.Bin;
import com.sipc.trash.service.ControlService;
import lombok.AllArgsConstructor;
import org.springframework.stereotype.Service;

@Service
@AllArgsConstructor
public class ControlServiceImpl implements ControlService {
    private MqttConfig mqttClient;
    private BinMapper binMapper;

    @Override
    public CommonResult<String> open(Integer binId) {
        Bin bin = binMapper.selectOne(new QueryWrapper<Bin>().eq("bin_id", binId));
        if (bin == null) {
            return CommonResult.fail("没有这个设备");
        }
        mqttClient.publish(1, false, "sipc/trash/" + bin.getBoardId() + "/open", "0");
        return CommonResult.success();
    }
}
