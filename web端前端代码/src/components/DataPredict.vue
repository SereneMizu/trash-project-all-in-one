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
    <div class="title">未来8天预测</div>
    <div
      style="
        position: absolute;
        display: flex;
        align-items: center;
        margin-left: 30%;
        margin-top: 1%;
        font-size: 20px;
        font-weight: bold;
        z-index: 100;
      "
    >
      <div style="width: 40%">选择集群</div>
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
          :value="item.cluster_id"
        />
      </el-select>
    </div>
    <div class="body-box">
      <div class="left-box">
        <div class="open-chart">
          <div ref="openOne" style="width: 100%; height: 100%"></div>
        </div>
        <div class="data-chart">
          <div ref="dataOne" style="width: 100%; height: 100%"></div>
          <div class="in-table">
            <div>
              <div>有害垃圾量</div>
              <div style="display: flex">
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
        <div class="little-title">危险预测</div>
        <div style="display: flex; height: 30%">
          <div
            style="
              display: flex;
              flex-direction: column;
              align-items: center;
              width: 70%;
            "
          >
            <div class="text">
              根据数据分析未来3天内边村甲烷数有超标的可能，请负责人员重点关注
            </div>
            <n-carousel draggable autoplay>
              <img class="carousel-img" src="../assets/甲烷2.jpg" />
              <img class="carousel-img" src="../assets/甲烷.jpg" />
            </n-carousel>
          </div>
          <div
            style="
              display: flex;
              justify-content: center;
              align-items: center;
              margin-left: 5%;
            "
          >
            <n-progress
              type="circle"
              :percentage="58"
              :offset-degree="180"
              color="green"
            />
          </div>
        </div>

        <div style="display: flex; height: 30%">
          <div
            style="
              display: flex;
              flex-direction: column;
              align-items: center;
              width: 70%;
            "
          >
            <div class="text">
              根据数据分析御溪园社区06号垃圾桶常有烟雾报警，请负责人员重点关注
            </div>
            <n-carousel draggable autoplay>
              <img class="carousel-img" src="../assets/烟雾2.jpg" />
              <img class="carousel-img" src="../assets/烟雾.jpg" />
            </n-carousel>
          </div>
          <div
            style="
              display: flex;
              justify-content: center;
              align-items: center;
              margin-left: 5%;
            "
          >
            <n-progress
              type="circle"
              :percentage="79"
              :offset-degree="180"
              color="green"
            />
          </div>
        </div>

        <div style="display: flex; height: 30%">
          <div
            style="
              display: flex;
              flex-direction: column;
              align-items: center;
              width: 70%;
            "
          >
            <div class="text">
              天津理工大学集群05号桶出现溢处破损，请相关人员及时收取垃圾和维修垃圾桶
            </div>
            <n-carousel draggable autoplay>
              <img class="carousel-img" src="../assets/装满2.jpg" />
              <img class="carousel-img" src="../assets/装满.jpg" />
            </n-carousel>
          </div>
          <div
            style="
              display: flex;
              justify-content: center;
              align-items: center;
              margin-left: 5%;
            "
          >
            <n-progress
              type="circle"
              :percentage="75"
              :offset-degree="180"
              color="green"
            />
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<style scoped lang="scss">
.carousel-img {
  width: 80%;
  height: 100%;
  border: 0px solid;
  border-radius: 5px;
  margin-left: 10%;
  object-fit: cover;
}
.main {
  width: 100%;
  height: 100%;
  .title {
    font-size: 36px;
    font-weight: bold;
    text-align: center;
    padding-top: 1%;
  }
  .body-box {
    width: 100%;
    height: 90%;
    display: flex;
    .left-box {
      width: 60%;
      height: 100%;
      .open-chart {
        margin-top: 2%;
        margin-left: 5%;
        width: 100%;
        height: 50%;
      }
      .data-chart {
        margin-top: 2%;
        margin-left: 5%;
        width: 100%;
        height: 45%;
        .in-table {
          position: absolute;
          margin-top: -20%;
          margin-left: 3%;
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
      width: 40%;
      height: 100%;
      .little-title {
        margin-top: 2%;
        font-size: 20px;
        font-weight: bold;
      }
      .text {
        font-size: 20px;
        color: rgba(86, 119, 34, 1);
        font-weight: bold;
        margin-top: 5%;
      }
    }
  }
}
</style>
<script setup lang="ts">
import { NProgress, NCarousel } from "naive-ui";
import { ref, onMounted, onUnmounted, nextTick, watch } from "vue";
import * as echarts from "echarts";
import request from "../utils/request";

const openOne = ref(null);
const dataOne = ref(null);
let chartInstance: any = null;
let chartInstanceOpen: any = null;
const cluster_id = ref(3);
const rubbishCate = ref([0, 0, 0, 0]);
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
const options = ref<any>([]);
async function getOpenData() {
  try {
    const response = await request.get(
      `/api/data/cluster/${cluster_id.value}/lid`
    );
    console.log(response);
    option.series[0].data = response.data.count;
    option.xAxis.data = response.data.date;
    chartInstanceOpen.setOption(option);
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
watch(cluster_id, () => {
  getOpenData();
  getDataData();
});
//数据存储
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
onMounted(async () => {
  await nextTick();
  chartInstanceOpen = echarts.init(openOne.value);
  chartInstanceOpen.setOption(option);
  chartInstance = echarts.init(dataOne.value);
  chartInstance.setOption(optionData);
});
onUnmounted(() => {
  if (chartInstance != null && chartInstance.dispose) {
    chartInstance.dispose();
  }
  if (chartInstanceOpen != null && chartInstanceOpen.dispose) {
    chartInstanceOpen.dispose();
  }
});
</script>
