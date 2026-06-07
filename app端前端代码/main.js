import App from './App';
import { ID_INJECTION_KEY } from 'element-plus'; // 导入 ID 注入键

// #ifndef VUE3
import Vue from 'vue';
import './uni.promisify.adaptor';
Vue.config.productionTip = false;
App.mpType = 'app';

const app = new Vue({
  ...App,
});

app.$mount();
// #endif

// #ifdef VUE3
import { createSSRApp } from 'vue';
import ElementPlus from 'element-plus';
import 'element-plus/dist/index.css';

export function createApp() {
  const app = createSSRApp(App);

  // 提供 ID 上下文
  app.provide(ID_INJECTION_KEY, {
    prefix: 2, // 设置合适的前缀
    current: 2, // 根据你的逻辑设置当前值
  });

  // 使用 Element Plus
  app.use(ElementPlus);

  return {
    app,
  };
}
// #endif
