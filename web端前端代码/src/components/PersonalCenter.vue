<template>
  <div style="width: 100%; height: 5%"></div>
  <div class="first-part">
    <div class="avatar">
      <el-upload
        method="put"
        :headers="headers"
        name="icon"
        :auto-upload="true"
        :show-file-list="false"
        :on-success="handleAvatarSuccess"
        :before-upload="beforeAvatarUpload"
      >
        <el-avatar :size="120" :src="imageUrl" />
      </el-upload>
    </div>
    <div class="name-part">
      <div>用户名： 宣宣</div>
      <div>工号： 123456</div>
      <div>注册时间：2024-08-02</div>
    </div>
    <div class="corre-part">
      <div class="status">
        <div style="width: 15%">认证状态</div>
        <div class="identity">已认证</div>
      </div>
      <div class="phone">
        <div style="width: 25%">手机号码： 123456789</div>
        <el-button type="text" class="button">修改</el-button>
      </div>
    </div>
  </div>
  <div class="second-part">
    <div class="change-part">
      <div class="email">
        <div style="width: 7%">邮箱</div>
        <el-input placeholder="请输入邮箱" style="width: 60%"></el-input>
      </div>
      <div class="position">
        <div style="width: 10%">负责区域</div>
        <el-select placeholder="Select" size="middle" style="width: 58%">
          <el-option
            v-for="item in options"
            :key="item.value"
            :label="item.label"
            :value="item.value"
          />
        </el-select>
      </div>
      <div class="introduction">
        <div style="width: 10%">个人简介</div>
        <el-input
          placeholder="请输入邮箱"
          style="width: 58%"
          type="textarea"
          :rows="3"
        ></el-input>
      </div>
      <div class="button-box">
        <el-button class="button-left">保存</el-button>
        <el-button class="button-right">重置</el-button>
      </div>
    </div>
    <div class="common-part">
      <div class="title">企业认证</div>
      <div class="line-one">
        <div style="width: 25%">账号类型： 企业账号</div>
        <div style="width: 25%" class="status">
          <div style="width: 35%">认证状态</div>
          <div class="identity">已认证</div>
        </div>
        <div style="width: 25%">认证时间： 2005-10-06</div>
      </div>
      <div class="line-two">
        <div style="width: 25%">法人姓名： 刘**</div>
        <div style="width: 25%">法人证件类型： 中国身份证</div>
        <div style="width: 25%">法人认证号码： 131****3246</div>
      </div>
      <div class="line-three">
        <div style="width: 25%">企业名称： 天津****有限公司</div>
        <div style="width: 25%">企业证件类型： 企业营业执照</div>
        <div style="width: 25%">组织机构代码： 5***9</div>
      </div>
    </div>
  </div>
  <div class="third-part">
    <div class="password line-part" style="padding-top: 1%">
      <div>
        登录密码&nbsp;&nbsp;&nbsp;已设置。密码至少6位字符，支持数字、字母和除空格外的特殊字符，且必须同时包含数字和大小写字母。
      </div>
      <el-button type="text">修改</el-button>
    </div>
    <hr />
    <div class="protect line-part">
      <div>
        密保问题&nbsp;&nbsp;&nbsp;您暂未设置密保问题，密保问题可以有效的保护账号的安全。
      </div>
      <el-button type="text">设置</el-button>
    </div>
    <hr />
    <div class="safe-phone line-part">
      <div>安全手机&nbsp;&nbsp;&nbsp;已绑定: 150******50</div>
      <el-button type="text">修改</el-button>
    </div>
    <hr />
    <div class="safe-email line-part">
      <div>
        安全邮箱&nbsp;&nbsp;&nbsp;您暂未设置邮箱，绑定邮箱可以用来找回密码、接收通知等。
      </div>
      <el-button type="text">设置</el-button>
    </div>
    <hr />
  </div>
</template>
<style scoped lang="scss">
.first-part {
  background-color: white;
  width: 100%;
  height: 20%;
  display: flex;
  align-items: center;
  .avatar {
    margin-left: 2%;
  }
  .name-part {
    display: flex;
    flex-direction: column;
    height: 60%;
    justify-content: space-around;
    color: rgba(78, 89, 105, 1);
    font-size: 14px;
    margin-left: 10%;
  }
  .corre-part {
    display: flex;
    width: 40%;
    height: 60%;
    justify-content: space-around;
    flex-direction: column;
    color: rgba(78, 89, 105, 1);
    font-size: 14px;
    margin-left: 25%;
    .status {
      display: flex;
      align-items: center;
      .identity {
        background-color: rgba(232, 255, 234, 1);
        color: rgba(45, 194, 79, 1);
        font-size: 12px;
        width: 10%;
        height: 100%;
        text-align: center;
      }
    }
    .phone {
      display: flex;
      align-items: center;
      .button {
        font-size: 12px;
      }
    }
  }
}
.second-part {
  width: 100%;
  height: 45%;
  display: flex;
  .change-part {
    margin-top: 3%;
    width: 100%;
    .email {
      color: rgba(136, 136, 136, 1);
      font-size: 14px;
      margin-left: 7%;
      display: flex;
      align-items: center;
    }
    .position {
      margin-top: 5%;
      color: rgba(136, 136, 136, 1);
      font-size: 14px;
      margin-left: 4%;
      display: flex;
      align-items: center;
    }
    .introduction {
      margin-top: 5%;
      color: rgba(136, 136, 136, 1);
      font-size: 14px;
      margin-left: 4%;
      display: flex;
      align-items: center;
    }
    .button-box {
      width: 75%;
      margin-top: 5%;
      height: 10%;
      display: flex;
      justify-content: space-around;
      .button-left {
        width: 12%;
        height: 100%;
        background-color: rgba(86, 119, 34, 1);
        color: white;
        font-size: 14px;
        font-weight: bold;
      }
      .button-right {
        width: 12%;
        height: 100%;
        font-size: 14px;
        font-weight: bold;
      }
    }
  }
  .common-part {
    width: 100%;
    .title {
      font-size: 28px;
      font-weight: bold;
      margin-top: 5%;
    }
    .line-one {
      display: flex;
      justify-content: space-between;
      margin-right: 5%;
      color: rgba(78, 89, 105, 1);
      font-size: 14px;
      margin-top: 5%;
      .status {
        display: flex;
        align-items: center;
        .identity {
          background-color: rgba(232, 255, 234, 1);
          color: rgba(45, 194, 79, 1);
          font-size: 12px;
          width: 30%;
          height: 100%;
          text-align: center;
        }
      }
    }
    .line-two {
      display: flex;
      justify-content: space-between;
      margin-right: 5%;
      color: rgba(78, 89, 105, 1);
      font-size: 14px;
      margin-top: 2%;
    }
    .line-three {
      display: flex;
      justify-content: space-between;
      margin-right: 5%;
      color: rgba(78, 89, 105, 1);
      font-size: 14px;
      margin-top: 2%;
    }
  }
}
.third-part {
  height: 30%;
  width: 100%;
  background-color: white;
  hr {
    width: 95%;
  }
  .line-part {
    height: 15%;
    font-size: 14px;
    color: rgba(78, 89, 105, 1);
    display: flex;
    align-items: center;
    justify-content: space-between;
    margin-left: 3%;
    margin-right: 3%;
  }
}
</style>
<script setup lang="ts">
import type { UploadProps } from "element-plus";
import { ref } from "vue";
const options: any = [];
let token: string | null;
token = localStorage.getItem("token");
const headers = {
  Authorization: `${token}`,
};
const imageUrl = ref("");
const handleAvatarSuccess: UploadProps["onSuccess"] = (_, uploadFile) => {
  imageUrl.value = URL.createObjectURL(uploadFile.raw!);
};

const beforeAvatarUpload: UploadProps["beforeUpload"] = (rawFile) => {
  const isJpgOrPng =
    rawFile.type === "image/jpeg" || rawFile.type === "image/png";

  if (!isJpgOrPng) {
    return false;
  } else if (rawFile.size / 1024 / 1024 > 2) {
    return false;
  }
  return true;
};
</script>
