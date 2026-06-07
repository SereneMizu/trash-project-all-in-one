package com.sipc.trash.mqtt;


import com.baomidou.mybatisplus.core.conditions.query.QueryWrapper;
import com.sipc.trash.mapper.*;
import com.sipc.trash.pojo.domain.PO.Bin;
import com.sipc.trash.pojo.domain.PO.Cluster;
import com.sipc.trash.pojo.domain.PO.Event;
import com.sipc.trash.pojo.domain.PO.Value;
import lombok.AllArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.eclipse.paho.client.mqttv3.IMqttDeliveryToken;
import org.eclipse.paho.client.mqttv3.MqttCallback;
import org.eclipse.paho.client.mqttv3.MqttMessage;
import org.springframework.stereotype.Component;

import java.util.Date;

@Slf4j
@Component
@AllArgsConstructor
public class MqttMessageCallBack implements MqttCallback {
    private final ClusterMapper clusterMapper;
    private final ValueMapper valueMapper;
    private BinMapper binMapper;
    private CountMapper countMapper;
    private EventMapper eventMapper;

    @Override
    public void connectionLost(Throwable throwable) {
        log.info("与服务器断开连接：{}", throwable.toString());
    }

    @Override
    public void messageArrived(String topic, MqttMessage mqttMessage) {
        // "sipc/trash/{board_id}/lid"
        // "sipc/trash/{board_id}/count"
        // "sipc/trash/{board_id}/value"
        // "sipc/trash/{board_id}/full"
        // "sipc/trash/{board_id}/danger"
        // "sipc/trash/{board_id}/break"
        log.info("MQTT CB, topic: {}", topic);
        String msg = new String(mqttMessage.getPayload());
        String[] topicArr = topic.split("/");
        String boardId = topicArr[2];
        String type = topicArr[3];
        // 获取 bin_id
        Bin bin = binMapper.selectOne(new QueryWrapper<Bin>().eq("board_id", boardId));
        Integer binId = bin.getBinId();
        String binName = bin.getBinName();
        Cluster cluster = clusterMapper.selectOne(new QueryWrapper<Cluster>().eq("cluster_id", bin.getClusterId()));
        String clusterName = cluster.getClusterName();

        countMapper.selectByDateAndId(binId);

        if (countMapper.selectByDateAndId(binId) == null) {
            countMapper.insertByBinId(binId);
        }

        switch (type) {
            case "lid": {
                countMapper.updateLidCount(binId);
                break;
            }
            case "count": {
                switch (msg) {
                    case "0":
                        countMapper.updateResidualWasteCount(binId);
                        break;
                    case "1":
                        countMapper.updateRecyclableCount(binId);
                        break;

                    case "2":
                        countMapper.updateFoodWasteCount(binId);
                        break;

                    case "3":
                        countMapper.updateHazardousWasteCount(binId);
                        break;
                }
                break;

            }
            case "value": {
                valueMapper.deleteOldData();

                Value value = new Value();
                try {
                    String[] strArr = msg.split(",");
                    value.setDate(new Date(System.currentTimeMillis()));
                    value.setMethaneValue(Float.valueOf(strArr[0]));
                    value.setSmogValue(Float.valueOf(strArr[1]));
                } catch (Exception e) {
                    log.error(e.getMessage());
                }


                if (value.getMethaneValue() > 128 || value.getSmogValue() > 128) {
                    Event event = new Event();
                    event.setEventName(clusterName + "集群" + binName + "垃圾桶烟雾含量超标");
                    event.setBinId(binId);
                    event.setStatus("报警");
                    event.setTrigger("机器筛选");
                    event.setEventTime(new Date(System.currentTimeMillis()));
                    eventMapper.insert(event);
                }
                value.setBinId(binId);
                valueMapper.insert(value);
                break;
            }
            case "full": {
                Event event = new Event();
                event.setEventName(clusterName + "集群" + binName + "垃圾桶满");
                event.setBinId(binId);
                event.setStatus("已满");
                event.setTrigger("机器筛选");
                event.setEventTime(new Date(System.currentTimeMillis()));
                eventMapper.insert(event);
                break;
            }
            case "danger": {
                System.out.println("before mapper");
                System.out.println("after mapper");
                Event event = new Event();
                event.setEventName(clusterName + "集群" + binName + "垃圾桶有危险");
                event.setBinId(binId);
                event.setStatus("报警");
                if (msg.equals("0")) {
                    event.setTrigger("人工");
                } else {
                    event.setTrigger("机器筛选");
                }
                event.setEventTime(new Date(System.currentTimeMillis()));
                eventMapper.insert(event);
                break;
            }
            case "break": {
                System.out.println("before mapper");
                System.out.println("after mapper");
                Event event = new Event();
                event.setEventName(clusterName + "集群" + binName + "垃圾桶破损");
                event.setBinId(binId);
                event.setStatus("维修");
                event.setTrigger("人工");
                event.setEventTime(new Date(System.currentTimeMillis()));
                eventMapper.insert(event);
                break;
            }
        }
//        System.out.println("cb ok");
    }

    @Override
    public void deliveryComplete(IMqttDeliveryToken iMqttDeliveryToken) {
        log.info("MQTT 接收消息成功");
    }
}
