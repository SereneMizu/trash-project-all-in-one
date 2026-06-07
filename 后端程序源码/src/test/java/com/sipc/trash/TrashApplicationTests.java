package com.sipc.trash;

import com.sipc.trash.mapper.CountMapper;
import com.sipc.trash.mapper.EventMapper;
import com.sipc.trash.mapper.UserMapper;
import com.sipc.trash.pojo.domain.DO.EventDetailDo;
import com.sipc.trash.pojo.domain.PO.Event;
import com.sipc.trash.pojo.domain.PO.User;
import com.sipc.trash.service.DataService;
import com.sipc.trash.util.MD5Utils;
import lombok.AllArgsConstructor;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;

import java.util.List;

@SpringBootTest
class TrashApplicationTests {
    @Autowired
    UserMapper userMapper;
    @Autowired
    EventMapper eventMapper;
    @Autowired
    private CountMapper countMapper;
    @Autowired
    private DataService dataService;

    @Test
    void contextLoads() {
        dataService.getClusterLid(3);
    }

}
