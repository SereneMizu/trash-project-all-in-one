<template>
  <div class="main">
    <img
      src="../assets/greenCircleDark.png"
      alt=""
      style="
        position: absolute;
        width: 10%;
        top: 0;
        right: 0;
        transform: translate(50%, -50%);
      "
    />
    <img
      src="../assets/greenCircleLight.png"
      alt=""
      width="3%"
      style="position: absolute; top: 5%; right: 3%"
    />
    <div class="left-box">
      <div class="welcome">
        <img src="../assets/applause.png" alt="" width="30px" />
        <div>欢迎回来，宣宣</div>
      </div>
      <div class="tip">
        <div style="font-size: 20px">
          今日tips：气温渐渐转凉，垃圾桶更易燃，请注意检测信息！
        </div>
        <div
          style="
            position: absolute;
            display: flex;
            align-items: center;
            margin-left: 25%;
            margin-top: -5%;
            font-size: 20px;
          "
        >
          <div>选择集群：</div>
          <el-select
            placeholder="请选择集群"
            size="small"
            v-model="cluster_id"
            style="width: 200px; font-size: 14px"
          >
            <el-option
              v-for="item in options"
              :key="item.cluster_id"
              :label="item.cluster_name"
              :value="item.cluster_id || 0"
            />
          </el-select>
        </div>
      </div>
      <div class="open">
        <div style="display: flex; width: 20%">
          <img src="../assets/垃圾桶.png" alt="" width="35px" height="35px" />
          <div style="margin-left: 15%">
            <div style="font-size: 12px">日开盖次数</div>
            <div style="font-size: 20px">{{ totalTimes }}次</div>
          </div>
        </div>
        <div
          style="
            font-size: 20px;
            width: 20%;
            color: rgba(78, 89, 105, 1);
            font-weight: bold;
          "
        >
          总开盖次数
        </div>
        <div style="display: flex; width: 20%">
          <img src="../assets/收益.png" alt="" width="35px" height="35px" />
          <div style="margin-left: 15%">
            <div style="font-size: 12px">较昨日变化</div>
            <div style="font-size: 20px">{{ rate }}%</div>
          </div>
        </div>
      </div>
      <div class="open-chart">
        <div ref="openOne" style="width: 100%; height: 100%"></div>
      </div>

      <div class="data-chart">
        <div ref="dataOne" style="width: 100%; height: 100%"></div>
        <div class="in-table">
          <div>
            <div>有害垃圾量</div>
            <div style="display: flex; margin-top: 10%">
              <img
                src="../assets/有害垃圾.png"
                alt=""
                width="28px"
                height="28px"
              />
              <div style="font-size: 26px">{{ rubbishCate[0] }}</div>
            </div>
          </div>
          <div>
            <div>厨余垃圾量</div>
            <div style="display: flex; margin-top: 10%">
              <img
                src="../assets/厨余垃圾2.png"
                alt=""
                width="28px"
                height="28px"
              />
              <div style="font-size: 26px">{{ rubbishCate[1] }}</div>
            </div>
          </div>
          <div>
            <div>可回收物量</div>
            <div style="display: flex; margin-top: 10%">
              <img
                src="../assets/可回收垃圾.png"
                alt=""
                width="28px"
                height="28px"
              />
              <div style="font-size: 26px">{{ rubbishCate[2] }}</div>
            </div>
          </div>
          <div>
            <div>其他垃圾量</div>
            <div style="display: flex; margin-top: 10%">
              <img
                src="../assets/其他垃圾.png"
                alt=""
                width="28px"
                height="28px"
              />
              <div style="font-size: 26px">{{ rubbishCate[3] }}</div>
            </div>
          </div>
        </div>
      </div>
    </div>
    <div class="right-box">
      <div class="title">数据检测</div>
      <div style="display: flex">
        <div class="littleTitle">当气体和烟雾浓度高于150标准值系统自动报警</div>
        <el-select
          placeholder="请选择垃圾桶"
          size="small"
          v-model="bin"
          style="width: 100px; font-size: 14px; margin-left: 5%"
        >
          <el-option
            v-for="item in options2"
            :key="item.binId"
            :label="item.binName"
            :value="item.binId || 0"
          />
        </el-select>
      </div>

      <div style="width: 100%; height: 30%; display: flex; margin-top: 5%">
        <div class="jw-chart">
          <div ref="jwOne" style="width: 100%; height: 100%"></div>
          <div style="text-align: center; width: 100%; font-weight: bold">
            甲烷检测
          </div>
        </div>

        <div class="smoke-chart">
          <div ref="smokeOne" style="width: 100%; height: 100%"></div>
          <div style="text-align: center; width: 100%; font-weight: bold">
            烟雾检测
          </div>
        </div>
      </div>
      <div style="display: flex; margin-top: 8%; align-items: center">
        <img src="../assets/line.jpg" alt="" width="30px" />
        <div style="font-size: 13px; font-weight: bold; width: 18%">
          最优路线
        </div>
        <img src="../assets/position.jpg" alt="" width="30px" />
        <div style="font-size: 13px; font-weight: bold; width: 18%">
          垃圾桶站点
        </div>
        <img src="../assets/redPosition.jpg" alt="" width="45px" />
        <div style="font-size: 13px; font-weight: bold; width: 18%">
          已满垃圾桶
        </div>
        <div
          style="
            font-size: 30px;
            font-weight: bold;
            margin-left: 20%;
            width: 30%;
          "
        >
          路线规划
        </div>
      </div>
      <div style="width: 100%; height: 35%; margin-top: 2%">
        <iframe
          src="../../static/map.html"
          frameborder="0"
          style="width: 100%; height: 100%"
        ></iframe>
      </div>
    </div>
  </div>
</template>
<script setup lang="ts">
import { ref, onMounted, onUnmounted, nextTick, watch } from "vue";
import * as echarts from "echarts";
import request from "../utils/request";
import router from "../router";
const openOne = ref(null);
const dataOne = ref(null);
const jwOne = ref(null);
const smokeOne = ref(null);
const totalTimes = ref();
const rate = ref();
const options2 = ref<any>([]);
const bin = ref(1);
const cluster_id = ref(3);
const rubbishCate = ref([0, 0, 0, 0]);
let chartInstanceOpen: any = null;
let chartInstance: any = null;
let chartInstanceJW: any = null;
let chartInstanceSmoke: any = null;
async function getGroup() {
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
      `/api/data/cluster/${cluster_id.value}/bin`
    );
    options2.value = response.data;
    console.log(response);
  } catch (error) {
    console.log(error);
  }
}
getContainer();
async function getOpenData() {
  try {
    const response = await request.get(
      `/api/data/cluster/${cluster_id.value}/lid`
    );
    console.log(response);
    option.series[0].data = response.data.count;
    option.xAxis.data = response.data.date;
    chartInstanceOpen.setOption(option);
    totalTimes.value = response.data.count[4];
    rate.value =
      (response.data.count[4] - response.data.count[3]) /
      response.data.count[4];
    rate.value = Number(rate.value.toFixed(1));
  } catch (error) {
    console.log(error);
  }
}
getOpenData();
async function getDataData() {
  try {
    const response = await request.get(
      `/api/data/cluster/${cluster_id.value}/rubbish`
    );
    optionData.xAxis.data = response.data.date;
    optionData.series[0].data = response.data.hazardous_waste_count;
    rubbishCate!.value[0] = response.data.hazardous_waste_count[4];
    optionData.series[1].data = response.data.recyclable_count;
    rubbishCate!.value[1] = response.data.recyclable_count[4];
    optionData.series[2].data = response.data.food_waste_count;
    rubbishCate!.value[2] = response.data.food_waste_count[4];
    optionData.series[3].data = response.data.residual_waste_count;
    rubbishCate!.value[3] = response.data.residual_waste_count[4];
    chartInstance.setOption(optionData);
    console.log(response);
  } catch (error) {
    console.log(error);
  }
}
getDataData();
async function getJWData() {
  try {
    const response = await request.get(`/api/data/bin/${bin.value}/methane`);
    console.log(response);
    optionJw.series[0].data = response.data.value;
    chartInstanceJW.setOption(optionJw);
  } catch (error) {
    console.log(error);
  }
}
getJWData();
async function getSmokeData() {
  try {
    const response = await request.get(`/api/data/bin/${bin.value}/smog`);
    console.log(response);
    optionSmoke.series[0].data = response.data.value;
    chartInstanceSmoke.setOption(optionSmoke);
  } catch (error) {
    console.log(error);
  }
}
getSmokeData();
async function getJWDataAgain() {
  try {
    const response = await request.get(`/api/data/bin/${bin.value}/methane`);
    console.log(response);
    for (let i = 0; i < 4; i++) {
      optionJw.series[0].data[i] = optionJw.series[0].data[i + 1];
    }
    optionJw.series[0].data[4] = response.data.value[4];
    for (let i = 0; i < 4; i++) {
      if (optionJw.series[0].data[i] > 150) {
        router.push("/warning");
      }
    }
    chartInstanceJW.setOption(optionJw);
  } catch (error) {
    console.log(error);
  }
}
async function getSmokeDataAgain() {
  try {
    const response = await request.get(`/api/data/bin/${bin.value}/smog`);
    console.log(response);
    for (let i = 0; i < 4; i++) {
      optionSmoke.series[0].data[i] = optionSmoke.series[0].data[i + 1];
    }
    optionSmoke.series[0].data[4] = response.data.value[4];
    for (let i = 0; i < 4; i++) {
      if (optionSmoke.series[0].data[i] > 150) {
        router.push("/warning");
      }
    }
    chartInstanceSmoke.setOption(optionSmoke);
  } catch (error) {
    console.log(error);
  }
}
watch(cluster_id, () => {
  getContainer();
  getOpenData();
  getDataData();
});
watch(bin, () => {
  getJWData();
  getSmokeData();
});
const setIntervalId = setInterval(() => {
  getJWDataAgain();
  getSmokeDataAgain();
}, 1000 * 60);
const option = {
  title: {
    text: "开盖次数(近5日)",
  },
  tooltip: {},
  xAxis: {
    splitLine: {
      show: false,
    },
    axisLine: {
      show: false,
    },
    axisTick: {
      show: false,
    },
    axisLabel: {
      show: true,
    },
    data: [
      "2024-09-17",
      "2024-09-18",
      "2024-09-19",
      "2024-09-20",
      "2024-09-21",
    ],
  },
  grid: {
    top: "20%",
    left: "5%",
    right: "10%",
    bottom: "10%",
  },
  yAxis: {
    splitLine: {
      show: false,
    },
  },
  series: [
    {
      stack: "Total",
      name: "开盖次数",
      type: "line",
      data: [160, 130, 250, 100, 80],
      smooth: true,
      lineStyle: {
        color: {
          type: "linear",
          x: 0,
          y: 0,
          x2: 1,
          y2: 1,
          colorStops: [
            { offset: 0, color: "rgb(36, 229, 254)" },
            { offset: 1, color: "rgb(111, 66, 251)" },
          ],
        },
        showSymbol: false,

        width: 2,
      },
      areaStyle: {
        opacity: 0.8,
        color: new echarts.graphic.LinearGradient(0, 0, 0, 1, [
          {
            offset: 0,
            color: "rgb(128, 255, 165,0.3)",
          },
          {
            offset: 1,
            color: "rgb(1, 191, 236,0)",
          },
        ]),
      },
    },
  ],
};
const optionData = {
  title: {
    text: "数据总览",
  },
  grid: {
    top: "30%",
    left: "5%",
    right: "10%",
    bottom: "10%",
  },
  tooltip: {},
  xAxis: {
    splitLine: {
      show: false,
    },
    axisLine: {
      show: false,
    },
    axisTick: {
      show: false,
    },
    axisLabel: {
      show: true,
    },
    data: [
      "2024-10-05",
      "2024-10-06",
      "2024-10-07",
      "2024-10-08",
      "2024-10-09",
    ],
  },
  yAxis: {
    splitLine: {
      show: false,
    },
  },
  series: [
    {
      stack: null,
      name: "有害垃圾量",
      type: "line",
      data: [400, 750, 820, 700, 650],
      smooth: true,
      lineStyle: {
        showSymbol: false,
        width: 2,
        color: "rgba(245, 166, 77,1)",
      },
      areaStyle: {
        opacity: 0.8,
        color: new echarts.graphic.LinearGradient(0, 0, 0, 1, [
          {
            offset: 0,
            color: "rgba(245, 166, 77,0.3)",
          },
          {
            offset: 1,
            color: "rgba(245, 166, 77,0)",
          },
        ]),
      },
    },
    {
      stack: null,
      name: "可回收物量",
      type: "line",
      data: [350, 570, 590, 250, 500],
      smooth: true,
      lineStyle: {
        showSymbol: false,
        width: 2,
        color: "rgba(79, 126, 248,1)",
      },
      areaStyle: {
        opacity: 0.8,
        color: new echarts.graphic.LinearGradient(0, 0, 0, 1, [
          {
            offset: 0,
            color: "rgba(79, 126, 248,0.3)",
          },
          {
            offset: 1,
            color: "rgba(79, 126, 248,0)",
          },
        ]),
      },
    },
    {
      stack: null,
      name: "厨余垃圾量",
      type: "line",
      data: [320, 370, 200, 350, 420],
      smooth: true,
      lineStyle: {
        showSymbol: false,
        width: 2,
        color: "rgba(90, 229, 224,1)",
      },
      areaStyle: {
        opacity: 0.8,
        color: new echarts.graphic.LinearGradient(0, 0, 0, 1, [
          {
            offset: 0,
            color: "rgba(90, 229, 224,0.3)",
          },
          {
            offset: 1,
            color: "rgba(90, 229, 224,0)",
          },
        ]),
      },
    },
    {
      stack: null,
      name: "其他垃圾量",
      type: "line",
      data: [420, 220, 420, 180, 280],
      smooth: true,
      lineStyle: {
        showSymbol: false,
        width: 2,
        color: "rgba(177, 13, 239,1)",
      },
      areaStyle: {
        opacity: 0.8,
        color: new echarts.graphic.LinearGradient(0, 0, 0, 1, [
          {
            offset: 0,
            color: "rgba(177, 13, 239,0.3)",
          },
          {
            offset: 1,
            color: "rgba(177, 13, 239,0)",
          },
        ]),
      },
    },
  ],
};
const optionJw = {
  title: {
    text: "",
  },
  grid: {
    top: "20%",
    left: "10%",
    right: "10%",
    bottom: "20%",
  },
  tooltip: {},
  xAxis: {
    data: ["", "", "", "", ""],
  },
  yAxis: {},
  series: [
    {
      stack: "Total",
      name: "甲烷数值",
      type: "line",
      data: [1],
      lineStyle: {
        color: "rgb(156, 171, 130)",
        showSymbol: false,

        width: 2,
      },
    },
  ],
};
const optionSmoke = {
  title: {
    text: "单位：ppm",
  },
  grid: {
    top: "20%",
    left: "10%",
    right: "10%",
    bottom: "20%",
  },
  tooltip: {},
  xAxis: {
    data: ["", "", "", "", ""],
  },
  yAxis: {},
  series: [
    {
      stack: "Total",
      name: "烟雾数值",
      type: "line",
      data: [2, 1, 2, 3, 5],
      lineStyle: {
        color: "rgb(156, 171, 130)",
        showSymbol: false,

        width: 2,
      },
    },
  ],
};

onMounted(async () => {
  await nextTick();
  chartInstanceOpen = echarts.init(openOne.value);
  chartInstanceOpen.setOption(option);
  chartInstance = echarts.init(dataOne.value);
  chartInstance.setOption(optionData);
  chartInstanceJW = echarts.init(jwOne.value);
  chartInstanceJW.setOption(optionJw);
  chartInstanceSmoke = echarts.init(smokeOne.value);
  chartInstanceSmoke.setOption(optionSmoke);
});
onUnmounted(() => {
  clearInterval(setIntervalId);
  if (chartInstance != null && chartInstance.dispose) {
    chartInstance.dispose();
  }
  if (chartInstanceOpen != null && chartInstanceOpen.dispose) {
    chartInstanceOpen.dispose();
  }
  if (chartInstanceJW != null && chartInstanceJW.dispose) {
    chartInstanceJW.dispose();
  }
  if (chartInstanceSmoke != null && chartInstanceSmoke.dispose) {
    chartInstanceSmoke.dispose();
  }
});
const options = ref<any>([]);
</script>
<style scoped lang="scss">
.main {
  width: 100%;
  height: 100%;
  display: flex;
}
.left-box {
  width: 55%;
  height: 100%;
  .welcome {
    display: flex;
    align-items: center;
    margin-left: 1.5%;
    margin-top: 1%;
    img {
      width: 30px;
    }
    div {
      font-size: 28px;
    }
  }
  .tip {
    display: flex;
    align-items: center;
    padding-left: 10%;
    margin-top: 2%;
    div {
      font-size: 18px;
      font-weight: bold;
    }
  }
  .open {
    margin-top: 4%;
    display: flex;
    justify-content: space-around;
    align-items: center;
  }
  .open-chart {
    margin-top: 2%;
    margin-left: 5%;
    width: 100%;
    height: 37%;
  }
  .data-chart {
    margin-top: 2%;
    margin-left: 5%;
    width: 100%;
    height: 37%;
    .in-table {
      position: absolute;
      margin-top: -19%;
      margin-left: 5%;
      width: 40%;
      display: flex;
      justify-content: space-around;
      div {
        font-size: 12px;
      }
    }
  }
}
.right-box {
  border-top-left-radius: 250px;
  width: 45%;
  height: 100%;
  background-color: rgb(246, 251, 240);
  .title {
    margin-top: 12%;
    font-size: 36px;
    font-weight: bold;
    text-align: center;
  }
  .littleTitle {
    font-size: 14px;
    margin-left: 25%;
    font-weight: bold;
    color: rgba(223, 12, 12, 1);
  }
  .jw-chart {
    width: 50%;
    height: 100%;
  }
  .smoke-chart {
    width: 50%;
    height: 100%;
  }
}
</style>
