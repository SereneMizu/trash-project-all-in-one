<template>
  <div class="main">
    <div class="circle" v-show="judge">
      <img
        src="../assets/警报.png"
        alt=""
        width="400px"
        style="margin-right: 50px; margin-top: -100px"
      />
      <div class="word" style="margin-top: 5%">
        位于天津理工大学集群的05号垃圾桶甲烷量超标
      </div>
      <div class="word" style="margin-top: 2%">有自燃隐患，请前往查看！</div>
      <div class="button" @click="showMap">前往查看</div>
    </div>
    <div class="map" v-if="!judge">
      <div style="width: 70%; height: 40%; margin-top: 20px">
        <iframe
          src="../../static/map.html"
          frameborder="0"
          style="width: 100%; height: 100%"
        ></iframe>
      </div>

      <div class="word" style="margin-top: 5%">
        位于天津理工大学集群的05号垃圾桶甲烷量超标
      </div>
      <div class="word" style="margin-top: 2%">有自燃隐患，请前往查看！</div>
      <div class="button" @click="disappear">知道了</div>
    </div>
  </div>
</template>
<script setup lang="ts">
import { ref } from "vue";
import router from "../router";
const judge = ref(true);
function showMap() {
  judge.value = false;
}
function disappear() {
  router.push("/datavisual");
}
</script>
<style scoped lang="scss">
.main {
  width: 100%;
  height: 100%;
  .circle {
    width: 700px;
    height: 700px;
    position: absolute;
    top: 50%;
    left: 50%;
    transform: translate(-50%, -50%);
    background-color: rgba(255, 255, 255, 1);
    border-radius: 50%;
    border: 0;
    display: flex;
    justify-content: center;
    flex-direction: column;
    align-items: center;
    .word {
      font-size: 28px;
      color: rgba(223, 12, 12, 1);
      font-weight: bold;
    }
    .button {
      background-color: rgba(233, 17, 17, 0.55);
      color: white;
      font-size: 14px;
      font-weight: bold;
      text-align: center;
      width: 120px;
      height: 50px;
      line-height: 50px;
      margin-top: 10%;
      cursor: pointer;
    }
  }
  .map {
    width: 700px;
    height: 700px;
    position: absolute;
    top: 50%;
    left: 50%;
    transform: translate(-50%, -50%);
    background-color: rgba(255, 255, 255, 1);
    border-radius: 50%;
    border: 0;
    display: flex;
    justify-content: center;
    flex-direction: column;
    align-items: center;
    .word {
      font-size: 28px;
      color: rgba(223, 12, 12, 1);
      font-weight: bold;
    }
    .button {
      background-color: rgba(233, 17, 17, 0.55);
      color: white;
      font-size: 14px;
      font-weight: bold;
      text-align: center;
      width: 120px;
      height: 50px;
      line-height: 50px;
      margin-top: 10%;
      cursor: pointer;
    }
  }
}
</style>
