<template>
  <div class="main">
    <div class="bac">
      <div
        style="
          background-color: rgb(255, 255, 255, 0.4);
          height: 100%;
          width: 100%;
        "
      >
        <div class="word" style="padding-top: 25%">智洁环控服务平台</div>
        <div class="word" style="padding-top: 5%">
          智能垃圾管理，开启绿色未来
        </div>
      </div>
    </div>
    <div class="body">
      <div class="title">登录</div>
      <div class="little-title">账号密码登录</div>
      <div class="input-box-credit">
        <img src="../assets/用户登录.png" alt="" width="60px" height="60px" />
        <el-input
          placeholder="请输入工号"
          class="input"
          v-model="account"
        ></el-input>
      </div>
      <div class="credit-box">
        <div class="error" v-show="judge">
          <img
            src="../assets/警告提示.png"
            alt=""
            width="40px"
            height="40px"
            v-show="judge"
          />
          <div>工号错误</div>
        </div>
      </div>
      <div class="input-box-password">
        <img
          src="../assets/登录页-密码.png"
          alt=""
          width="60px"
          height="60px"
        />
        <el-input
          placeholder="请输入密码"
          class="input"
          v-model="password"
          type="password"
        ></el-input>
      </div>
      <div class="password-box">
        <div class="error">
          <img
            src="../assets/警告提示.png"
            alt=""
            width="40px"
            height="40px"
            v-show="judge"
          />
          <div v-show="judge">密码错误</div>
        </div>
        <el-button type="text" class="forget" @click="toForget"
          >忘记密码</el-button
        >
      </div>
      <el-button class="login-button" @click="login">登录</el-button>
      <div class="enrol-box">
        <div class="no-credit">没有账号？</div>
        <el-button type="text" class="enrol" @click="toEnrol">注册</el-button>
      </div>
    </div>
  </div>
</template>
<script setup lang="ts">
import { ref } from "vue";
import request from "../utils/request";
import router from "../router";
const account = ref("");
const password = ref("");
const judge = ref(false);
function toForget() {
  router.push("/forget");
}
function toEnrol() {
  router.push("/enrol");
}
async function login() {
  judge.value = false;
  try {
    const response = await request.post("/api/user/login", {
      account: account.value,
      password: password.value,
    });
    console.log(response);
    localStorage.setItem("token", response.data.token);
    router.push("/datavisual");
  } catch {
    judge.value = true;
  }
}
</script>
<style scoped lang="scss">
.main {
  width: 100vw;
  height: 100vh;
  display: flex;
  .bac {
    background-image: url("../assets/首页背景.jpg");
    background-size: cover;
    background-position: center;
    width: 65%;
    height: 100%;
    .word {
      font-size: 72px;
      font-weight: bold;
      text-align: center;
    }
  }
  .body {
    width: 35%;
    background-color: rgba(228, 246, 200, 0.61);
    display: flex;
    align-items: center;
    flex-direction: column;
    padding-top: 12%;
    .title {
      font-size: 48px;
      font-weight: bold;
    }
    .little-title {
      margin-top: 5%;
      font-size: 36px;
      font-weight: bold;
    }
    .input-box-credit {
      margin-top: 5%;
      width: 75%;
      padding-left: 15%;
      display: flex;
      justify-content: flex-start;
      align-items: center;
      margin-top: 10%;

      .input {
        margin-left: 5%;
        width: 60%;
        height: 80%;
        border-radius: 5%;
        font-weight: bold;
        font-size: 18px;
      }
    }
    .input-box-password {
      width: 75%;
      padding-left: 15%;
      display: flex;
      justify-content: flex-start;
      align-items: center;
      .input {
        margin-left: 5%;
        width: 60%;
        height: 80%;
        border-radius: 5%;
        font-weight: bold;
        font-size: 18px;
      }
    }
    .credit-box {
      width: 45%;
      height: 6%;
      display: flex;
      .error {
        display: flex;
        align-items: center;
        font-size: 18px;
        color: rgba(233, 17, 17, 0.55);
      }
    }
    .password-box {
      width: 75%;
      height: 6%;
      display: flex;
      align-items: center;
      .forget {
        position: absolute;
        margin-left: 18%;
        font-size: 20px;
        color: rgba(11, 67, 238, 1);
        font-weight: bold;
        text-decoration: underline;
      }
      .error {
        margin-left: 20%;
        display: flex;
        align-items: center;
        font-size: 18px;
        color: rgba(233, 17, 17, 0.55);
      }
    }
    .login-button {
      margin-top: 5%;
      font-size: 28px;
      color: white;
      width: 20%;
      height: 5%;
      background-color: rgba(208, 225, 133, 1);
    }
    .login-button:hover {
      background-color: rgba(71, 98, 29, 0.74);
    }
    .enrol-box {
      display: flex;
      align-items: center;
      margin-top: 10%;
      .enrol {
        font-size: 20px;
        color: rgba(11, 67, 238, 1);
        font-weight: bold;
        text-decoration: underline;
      }
      .no-credit {
        font-size: 20px;
        font-weight: bold;
      }
    }
  }
}
</style>
