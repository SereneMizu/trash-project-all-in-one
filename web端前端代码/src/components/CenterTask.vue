<template>
  <el-container class="bac">
    <el-aside width="200px">
      <el-menu class="menu">
        <div
          style="
            display: flex;
            align-items: center;
            margin-top: 10%;
            margin-left: 5%;
          "
        >
          <img src="../assets/logo.png" alt="" width="50px" class="logo" />
          <div class="word">智洁环控</div>
        </div>
        <el-menu-item index="1" style="margin-top: 70%" @click="changeOne">
          <img src="../assets/数据可视化1.png" alt="" width="60px" />
          <div class="word">数据分析</div>
        </el-menu-item>
        <br />
        <el-menu-item index="2" @click="changeTwo">
          <img src="../assets/数据预测.png" alt="" width="60px" />
          <div class="word">数据预测</div>
        </el-menu-item>
        <br />
        <el-menu-item index="3" @click="changeThree">
          <img src="../assets/列表.png" alt="" width="60px" />
          <div class="word">事件列表</div>
        </el-menu-item>
        <br />
        <el-menu-item index="4" @click="changeFour">
          <img src="../assets/用户登录2.png" alt="" width="60px" />
          <div class="word">个人中心</div>
        </el-menu-item>
        <br />
        <el-menu-item index="5" @click="quit">
          <img src="../assets/退出登录.png" alt="" width="60px" />
          <div class="word">退出登录</div>
        </el-menu-item>
      </el-menu>
      <img
        src="../assets/greenCircle.png"
        alt=""
        style="position: absolute; margin-top: 5%; margin-left: 2%"
      />
    </el-aside>

    <el-container>
      <el-main class="main">
        <div
          v-show="judge"
          style="
            position: absolute;
            z-index: 5;
            width: 20vw;
            height: 25vh;
            background-color: white;
            top: 50%;
            left: 50%;
            transform: translate(-50%, -50%);
          "
        >
          <div
            style="
              display: flex;
              align-items: center;
              margin-left: 5%;
              margin-top: 5%;
            "
          >
            <img
              src="../assets/警告提示.png"
              alt=""
              width="30px"
              height="30px"
            />
            <div
              style="
                font-weight: bold;
                font-size: 16px;
                color: rgba(130, 129, 129, 1);
                margin-left: 3%;
              "
            >
              提示
            </div>
          </div>
          <div
            style="
              font-size: 18px;
              color: black;
              justify-content: center;
              display: flex;
              font-weight: bold;
              margin-top: 8%;
            "
          >
            您确定要退出吗
          </div>
          <div
            style="
              font-size: 18px;
              color: black;
              justify-content: center;
              display: flex;
              font-weight: bold;
              margin-top: 3%;
            "
          >
            退出后内容不再保存
          </div>
          <div
            style="
              display: flex;
              justify-content: space-around;
              margin-top: 5%;
              height: 15%;
            "
          >
            <button
              style="
                background-color: rgba(64, 91, 20, 1);
                color: white;
                width: 20%;
                height: 100%;
              "
              @click="toLogin"
            >
              确定
            </button>
            <button style="width: 20%; height: 100%" @click="disappear">
              取消
            </button>
          </div>
        </div>
        <router-view></router-view>
      </el-main>
    </el-container>
  </el-container>
</template>
<script setup lang="ts">
import { ref } from "vue";
import { useRouter } from "vue-router";
const router = useRouter();
const judge = ref(false);
function changeOne() {
  router.push("/datavisual");
}
function changeTwo() {
  router.push("/datapredict");
}
function changeThree() {
  router.push("/datalist");
}
function changeFour() {
  router.push("/personalcenter");
}
function quit() {
  judge.value = true;
}
function toLogin() {
  router.push("/login");
}
function disappear() {
  judge.value = false;
}
</script>
<style scoped lang="scss">
:deep(.el-table__row) {
  background-color: transparent;
}
.bac {
  width: 100vw;
  height: 100vh;
  background-color: rgba(228, 246, 200, 0.61);
}
.el-aside {
  border: 0;
  border-top-right-radius: 75px;
  background-color: rgb(234, 234, 234);
  .menu {
    background-color: rgb(234, 234, 234);
    .word {
      font-size: 28px;
      color: rgba(86, 119, 34, 1);
    }
    .el-menu-item {
      .word {
        font-size: 20px;
        margin-left: 10%;
        color: rgba(86, 119, 34, 1);
      }
    }
  }
}
.main {
  border: 0;
  padding: 0;
  margin: 0;
}
</style>
