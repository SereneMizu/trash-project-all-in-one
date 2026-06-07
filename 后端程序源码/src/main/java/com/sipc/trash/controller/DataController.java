package com.sipc.trash.controller;

import com.sipc.trash.pojo.CommonResult;
import com.sipc.trash.pojo.domain.DO.EventDetailDo;
import com.sipc.trash.pojo.model.request.DataEventRequest;
import com.sipc.trash.pojo.model.result.*;
import com.sipc.trash.service.DataService;
import lombok.AllArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.web.bind.annotation.*;

import java.text.ParseException;
import java.util.List;

@Slf4j
@RestController
@AllArgsConstructor
@RequestMapping("/data")
public class DataController {
    private DataService dataService;

    @GetMapping("/cluster")
    public CommonResult<List<DataClusterResultItem>> getClusterList() {
        return dataService.getClusterList();
    }

    @GetMapping("/cluster/{cluster_id}/lid")
    public CommonResult<DataClusterLidResult> getClusterLid(@PathVariable("cluster_id") Integer clusterId) {
        return dataService.getClusterLid(clusterId);
    }

    @GetMapping("/cluster/{cluster_id}/rubbish")
    public CommonResult<DataClusterRubbishResult> getClusterRubbish(@PathVariable("cluster_id") Integer clusterId) {
        log.info("clusterId:{}", clusterId);
        return dataService.getClusterRubbish(clusterId);
    }

    @GetMapping("/cluster/{cluster_id}/bin")
    public CommonResult<List<DataClusterBinResultItem>> getClusterBinList(@PathVariable("cluster_id") Integer clusterId) {
        log.info("查询{}号集群", clusterId);
        return dataService.getClusterBinList(clusterId);
    }

    @GetMapping("/bin/{bin_id}/methane")
    public CommonResult<DataClusterBinMethaneResult> getClusterBinMethane(@PathVariable("bin_id") Integer binId) {
        return dataService.getClusterBinMethane(binId);
    }

    @GetMapping("/bin/{bin_id}/smog")
    public CommonResult<DataClusterBinSmogResult> getClusterBinSmog(@PathVariable("bin_id") Integer binId) {
        return dataService.getClusterBinSmog(binId);
    }

    @PostMapping("/event")
    public CommonResult<List<EventDetailDo>> getEventList(@RequestBody DataEventRequest request) {
        return dataService.getEventList(request);
    }

    @DeleteMapping("/event/{event_id}")

    public CommonResult<String> deleteEvent(@PathVariable("event_id") Integer eventId) {
        return dataService.deleteEvent(eventId);
    }

}
