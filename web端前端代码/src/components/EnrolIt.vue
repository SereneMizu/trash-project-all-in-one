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
      <div class="title">注册</div>
      <div class="little-title">注册一个新账户</div>
      <div class="input-box-credit">
        <img src="../assets/用户登录.png" alt="" width="60px" height="60px" />
        <el-input
          placeholder="请输入账号"
          class="input"
          v-model="account"
        ></el-input>
      </div>
      <div class="input-box-password">
        <img src="../assets/用户登录.png" alt="" width="60px" height="60px" />
        <el-input
          placeholder="请输入用户名"
          class="input"
          v-model="username"
        ></el-input>
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
        ></el-input>
      </div>
      <div class="input-box-password">
        <img
          src="../assets/登录页-密码.png"
          alt=""
          width="60px"
          height="60px"
        />
        <el-input
          placeholder="请再次输入密码"
          class="input"
          v-model="passwordAgain"
        ></el-input>
      </div>
      <el-button class="login-button" @click="enrol">注册</el-button>
      <div class="enrol-box">
        <div class="no-credit">已有账号：</div>
        <el-button type="text" class="enrol" @click="toHomepage"
          >登录</el-button
        >
      </div>
    </div>
  </div>
</template>
<script setup lang="ts">
import { ref } from "vue";
import router from "../router";
import request from "../utils/request";
const account = ref("");
const password = ref("");
const username = ref("");
const passwordAgain = ref("");
function toHomepage() {
  router.push("/login");
}
async function enrol() {
  try {
    const response = await request.post("/api/user/register", {
      account: account.value,
      password: password.value,
      username: username.value,
    });
    console.log(response);
    router.push("/");
  } catch {}
}
</script>
<style scoped lang="scss">
.in-button {
  position: absolute;
  z-index: 1;
  width: 5%;
  height: 3%;
  border-radius: 5px;
  margin-left: 15%;
  font-size: 12px;
  background-color: rgba(89, 138, 199, 1);
  color: white;
  cursor: pointer;
  outline: none;
  display: flex;
  justify-content: center;
  align-items: center;
}
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
    padding-top: 8%;
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
      margin-top: 4%;
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
      margin-top: 4%;
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
      justify-content: space-between;
      .forget {
        margin-right: 10%;
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
      margin-top: 3%;
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
