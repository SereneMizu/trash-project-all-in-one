import { createRouter, createWebHistory } from "vue-router";

const routes = [
  {
    path: "/login",
    component: () => import("../components/LoginIt.vue"),
  },
  {
    path: "/forget",
    component: () => import("../components/ForgetPassword.vue"),
  },
  {
    path: "/enrol",
    component: () => import("../components/EnrolIt.vue"),
  },
  {
    path: "/",
    redirect: "/login",
    component: () => import("../components/CenterTask.vue"),
    children: [
      {
        path: "datavisual",
        component: () => import("../components/DataVisual.vue"),
      },
      {
        path: "warning",
        component: () => import("../components/WarningBox.vue"),
      },
      {
        path: "datalist",
        component: () => import("../components/DataList.vue"),
      },
      {
        path: "datapredict",
        component: () => import("../components/DataPredict.vue"),
      },
      {
        path: "personalcenter",
        component: () => import("../components/PersonalCenter.vue"),
      },
    ],
  },
];

const router = createRouter({
  history: createWebHistory(),
  routes,
});

export default router;
