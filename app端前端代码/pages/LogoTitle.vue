<template>
	<view class="title">
		<view class="img-box">
			<image src="../static/logo.png" mode="" class="logo"></image>
			<view class="word">
				智洁环控
			</view>
		</view>
		<view class="group-choose">
			<view class="group-word">
				选择集群:
			</view>
			<view class="group-select">
				<picker @change="bindPickerChange" :value="index" :range="array">
					<view class="uni-input">{{array[index]}}</view>
				</picker>
			</view>
		</view>
	</view>
</template>

<script lang="ts" setup>
	import { ref } from "vue";
	const array = ref(['天津理工大学', '美国', '巴西', '日本'])
	const index = ref(0);
	const cluster_id = ref(3)
	const options = ref();
	const token = uni.getStorageSync('token');
	const bindPickerChange = function (e) {
		index.value = e.detail.value;
		cluster_id.value = options.value[index.value].cluster_id;
		uni.setStorageSync('clusterId', cluster_id.value)
	};
	async function getGroup() {
		uni.request({
			url: 'https://trash.sipc115.com/api/data/cluster',
			method: 'GET',
			header: {
				'Authorization': token,
			},
			success: (res) => {
				console.log(res.data);
				options.value = res.data.data;
				for (let i = 0; i < options.value.length; i++) {
					array.value[i] = res.data.data[i].cluster_name;
				}
			}
		});
	}
	getGroup()
</script>

<style lang="scss" scoped>
	.title {
		display: flex;
		justify-content: space-between;
		align-items: center;
		padding-top: 3%;
		font-size: 18rpx;

		.img-box {
			display: flex;
			align-items: center;
			margin-left: 5%;
			height: 10%;
			width: 100%;

			.logo {
				width: 80rpx;
				height: 80rpx;
			}

			.word {
				font-size: 35rpx;
				color: rgba(86, 119, 34, 1);
				font-weight: bold;
			}
		}

		.group-choose {
			font-weight: bold;
			width: 50%;
			height: 50rpx !important;
			font-size: 20rpx;
			margin-right: 5%;
			border-radius: 5px;
			display: flex;
			justify-content: center;
			align-items: center;
			background-color: white;
		}
	}
</style>