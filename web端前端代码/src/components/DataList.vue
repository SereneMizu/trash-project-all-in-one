<template>
  <div class="main">
    <div class="title">数据列表</div>
    <div class="first-line">
      <div style="width: 5%">垃圾桶名称</div>
      <el-select
        placeholder="请选择集群"
        size="small"
        v-model="queryData.cluster_id"
        style="width: 20%"
      >
        <el-option
          v-for="item in options"
          :key="item.cluster_id"
          :label="item.cluster_name"
          :value="item.cluster_id || 0"
        />
      </el-select>
      <div style="width: 5%; margin-left: 6%">所在集群</div>
      <el-select
        placeholder="请选择垃圾桶"
        size="small"
        v-model="queryData.bin_id"
        style="width: 20%"
      >
        <el-option
          v-for="item in options2"
          :key="item.binId"
          :label="item.binName"
          :value="item.binId || 0"
        />
      </el-select>
      <div style="width: 5%; margin-left: 4%">垃圾桶状态</div>
      <el-select
        placeholder="请选择垃圾桶状态"
        size="small"
        v-model="queryData.status"
        style="width: 22%"
      >
        <el-option
          v-for="item in optionsStatus"
          :key="item.status"
          :label="item.status"
          :value="item.status"
        />
      </el-select>
      <el-button
        style="
          width: 5%;
          height: 100%;
          background-color: rgba(86, 119, 34, 1);
          color: white;
          margin-left: 1%;
        "
        @click="getEvent"
        >查询</el-button
      >
    </div>
    <div class="second-line">
      <div style="width: 5%">触发方式</div>
      <el-select
        placeholder="请选择触发方式"
        size="small"
        v-model="queryData.trigger"
        style="width: 20%"
      >
        <el-option
          v-for="item in optionsTri"
          :key="item.tri"
          :label="item.tri"
          :value="item.tri"
        />
      </el-select>
      <div style="width: 4.5%; margin-left: 35%">查询时间</div>
      <div>
        <el-date-picker
          type="daterange"
          start-placeholder="开始日期"
          end-placeholder="结束日期"
          style="margin-left: 10px"
          v-model="dataRange"
          :start-date.sync="queryData.start_time"
          :end-date.sync="queryData.end_time"
          value-format="yyyy-MM-DD"
        />
      </div>
      <el-button
        style="
          width: 5%;
          height: 100%;
          background-color: white;
          color: black;
          margin-left: 1%;
        "
        >刷新</el-button
      >
    </div>
    <hr style="margin-top: 1%" />
    <div class="third-line">
      <img src="../assets/警告提示.png" alt="" width="40px" class="gap" />
      <div class="gap">垃圾已满</div>
      <img src="../assets/烟雾报警.png" alt="" width="40px" class="gap" />
      <div class="gap">烟雾报警</div>
      <img src="../assets/维修服务.png" alt="" width="40px" class="gap" />
      <div class="gap">需要维修</div>
    </div>
    <el-table
      :data="mainData"
      style="
        width: 90%;
        margin-left: 5%;
        height: 60%;
        background-color: transparent !important;
        height: 60%;
        margin-top: 2%;
      "
    >
      <el-table-column
        prop="cluster_name"
        label="所在集群"
        :resizable="false"
      />
      <el-table-column prop="bin_name" label="垃圾桶名称" :resizable="false" />
      <el-table-column prop="status" label="垃圾桶状态" :resizable="false">
        <template #default="scope">
          <div
            style="display: flex; align-items: center; font-size: 18px"
            v-show="scope.row.status == '已满'"
          >
            <img src="../assets/警告提示.png" alt="" width="40px" />
            <el-button link type="text" style="color: blue" class="detail"
              >查看详情</el-button
            >
          </div>
          <div
            style="display: flex; align-items: center; font-size: 18px"
            v-show="scope.row.status == '报警'"
          >
            <img src="../assets/烟雾报警.png" alt="" width="40px" />
            <el-button link type="text" style="color: blue" class="detail"
              >查看详情</el-button
            >
          </div>
          <div
            style="display: flex; align-items: center; font-size: 18px"
            v-show="scope.row.status == '维修'"
          >
            <img src="../assets/维修服务.png" alt="" width="40px" />
            <el-button link type="text" style="color: blue" class="detail"
              >查看详情</el-button
            >
          </div>
        </template>
      </el-table-column>
      <el-table-column prop="trigger" label="筛选方式" :resizable="false" />
      <el-table-column prop="event_time" label="创建时间" :resizable="false" />
    </el-table>
  </div>
</template>
<script setup lang="ts">
import { ref } from "vue";
import request from "../utils/request";
import { SearchData } from "../api/main";
const options = ref<any>([]);
const options2 = ref<any>([]);
const dataRange = ref([]);
const mainData = ref();
const optionsStatus = ref([
  {
    status: "已满",
  },
  {
    status: "报警",
  },
  {
    status: "维修",
  },
]);
const optionsTri = ref([
  {
    tri: "机器筛选",
  },
  {
    tri: "人工",
  },
]);
const queryData = ref<SearchData>({
  cluster_id: "",
  bin_id: "",
  status: "",
  trigger: "",
  start_time: "",
  end_time: "",
});
async function getGroup() {
  console.log(dataRange.value);

  try {
    const response = await request.get("/api/data/cluster");
    console.log(response);
    options.value = response.data;
  } catch (error) {
    console.log(error);
  }
}
getGroup();
async function getContainer() {
  try {
    const response = await request.get(
      `/api/data/cluster/${queryData.value.cluster_id || 3}/bin`
    );
    options2.value = response.data;
    console.log(response);
  } catch (error) {
    console.log(error);
  }
}
getContainer();
async function getEvent() {
  console.log(dataRange.value);
  queryData.value.start_time = dataRange.value[0];
  queryData.value.end_time = dataRange.value[1];
  try {
    const response = await request.post("/api/data/event", queryData.value);
    mainData.value = response.data;
    console.log(response);
  } catch (error) {
    console.log(error);
  }
}
getEvent();
</script>
<style scoped lang="scss">
.main {
  width: 99%;
  height: 100%;
  .title {
    font-size: 28px;
    font-weight: bold;
    padding-top: 1%;
    padding-left: 1%;
  }
  .first-line {
    display: flex;
    padding-top: 2%;
    padding-left: 1%;
    align-items: center;
    font-weight: bold;
    width: 100%;
    font-size: 14px;
    color: rgba(78, 89, 105, 1);
  }
  .second-line {
    display: flex;
    padding-top: 2%;
    padding-left: 1%;
    align-items: center;
    font-weight: bold;
    width: 100%;
    font-size: 14px;
    color: rgba(78, 89, 105, 1);
  }
  .third-line {
    display: flex;
    align-items: center;
    margin-top: 1%;
    margin-left: 2%;
    font-size: 20px;
    font-weight: bold;
    .gap {
      margin-right: 1%;
    }
  }
  .detail:focus::after {
    content: "";
    position: absolute;
    z-index: 9999;
    left: -50%;
    top: 50%;
    transform: translateY(-10%);
    width: 150px;
    height: 150px;
    background-image: url("../assets/冒烟.jpg");
    background-size: cover;
    transition: right 0.3s ease;
  }
}
</style>
