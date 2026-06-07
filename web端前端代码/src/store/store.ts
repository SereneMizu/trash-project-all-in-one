import { defineStore } from "pinia";
import { ref } from "vue";
export const useStore = defineStore("homePage", () => {
  const data = ref([
    {
      cluster_name: "御溪园社区集群",
      bin_id: 232,
      status: 1,
      trigger: "机器筛选",
      date: "2024-09-02 10：30",
    },
    {
      cluster_name: "天津理工大学集群",
      bin_id: 254,
      status: 3,
      trigger: "人工",
      date: "2024-09-07 1：21",
    },
    {
      cluster_name: "边村集群",
      bin_id: 46,
      status: 1,
      trigger: "机器筛选",
      date: "2024-09-10 11：28",
    },
    {
      cluster_name: "天津理工大学集群",
      bin_id: 577,
      status: 1,
      trigger: "机器筛选",
      date: "2024-09-14 5：13",
    },
    {
      cluster_name: "边村集群",
      bin_id: 232,
      status: 2,
      trigger: "机器筛选",
      date: "2024-09-17 12：30",
    },
    {
      cluster_name: "天津理工大学集群",
      bin_id: 254,
      status: 3,
      trigger: "人工",
      date: "2024-09-20 10：30",
    },
    {
      cluster_name: "御溪园社区集群",
      bin_id: 46,
      status: 3,
      trigger: "机器筛选",
      date: "2024-09-22 7：30",
    },
    {
      cluster_name: "天津理工大学集群",
      bin_id: 577,
      status: 1,
      trigger: "机器筛选",
      date: "2024-09-25 6：45",
    },
    {
      cluster_name: "边村集群",
      bin_id: 232,
      status: 2,
      trigger: "机器筛选",
      date: "2024-09-28 7：46",
    },
    {
      cluster_name: "天津理工大学集群",
      bin_id: 254,
      status: 3,
      trigger: "人工",
      date: "2024-09-29 11：30",
    },
  ]);
  return { data };
});
