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
      <div class="title">忘记密码</div>
      <div class="little-title">验证码登录</div>
      <div class="input-box-credit">
        <img src="../assets/用户登录.png" alt="" width="60px" height="60px" />
        <el-input
          placeholder="请输入手机号"
          class="input"
          v-model="account"
        ></el-input>
      </div>
      <div class="input-box-password">
        <img src="../assets/验证码.png" alt="" width="60px" height="60px" />
        <el-input
          placeholder="请输入验证码"
          class="input"
          v-model="password"
        ></el-input>
        <div
          class="in-button"
          ref="emailMsg"
          @click="emailIt"
          :disabled="emailMsgJudge"
        >
          <div>发送验证码</div>
        </div>
      </div>
      <el-button class="login-button">登录</el-button>
      <div class="enrol-box">
        <div class="no-credit">想起密码：</div>
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
const account = ref("");
const emailMsg = ref<HTMLElement>();
const emailMsgNum = ref<number>(60);
const intervalId = ref<number | null>(null);
const emailMsgJudge = ref<boolean>(false);
const password = ref("");
function toHomepage() {
  router.push("/login");
}
async function emailIt() {
  emailMsg.value!.style.backgroundColor = "gray";
  emailMsg.value!.textContent = `${emailMsgNum.value}s`;

  emailMsgJudge.value = true;
  intervalId.value = Number(
    setInterval(() => {
      if (emailMsgNum.value) emailMsgNum.value--;
      emailMsg.value!.textContent = `${emailMsgNum.value}s`;
      if (emailMsgNum.value === 0) {
        clearInterval(Number(intervalId.value));
        emailMsg.value!.style.backgroundColor = "rgba(89, 138, 199, 1)";
        emailMsg.value!.textContent = `发送验证码`;
        emailMsgNum.value = 60;
        emailMsgJudge.value = false;
      }
    }, 1000)
  );
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
      margin-top: 5%;
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
