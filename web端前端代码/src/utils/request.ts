import axios, { InternalAxiosRequestConfig, AxiosResponse } from "axios";
import { ElMessageBox, ElLoading, ElMessage } from "element-plus";

const request = axios.create({
  // baseURL: "https://trash.sipc115.com/api",
  timeout: 5000,
});

let loadingInstance: any = null;
// 可根据项目实际情况自行更改

request.interceptors.request.use(
  (config: InternalAxiosRequestConfig) => {
    let token: string | null = null;
    token = localStorage.getItem("token");

    if (token) config.headers.Authorization = token;
    loadingInstance = ElLoading.service({
      lock: true,
      text: "加载中...",
      background: "rgba(255, 255, 255, 0.6)",
    });

    return config;
  },
  (error) => {
    if (loadingInstance) loadingInstance.close();
    Promise.reject(error);
  }
);

request.interceptors.response.use(
  (response: AxiosResponse) => {
    if (loadingInstance) loadingInstance.close();
    const { code, message } = response.data;
    // 登录成功
    if (code === "00000") {
      return response.data;
    }
    ElMessage.error(message || "系统出错");
    return Promise.reject(new Error(message || "Error"));
  },
  (error: any) => {
    if (loadingInstance) loadingInstance.close();
    if (error.response.data) {
      const { msg, code } = error.response.data;
      // token 过期，跳转登录页
      if (code === "A0230") {
        ElMessageBox.confirm("当前页面已失效，请重新登录", "提示", {
          confirmButtonText: "确定",
          type: "warning",
        }).then(() => {
          localStorage.clear();
          window.location.href = "/login";
        });
      } else {
        ElMessage.error(msg || "系统出错");
      }
    }
    return Promise.reject(error.message);
  }
);

export default request;
