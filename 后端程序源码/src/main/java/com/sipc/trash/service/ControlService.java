package com.sipc.trash.service;

import com.sipc.trash.pojo.CommonResult;

public interface ControlService {
    CommonResult<String> open(Integer binId);
}
