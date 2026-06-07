<template>
	<view class="content">
		<view class="mask">
			<image class="logo" src="/static/logo1.png"></image>
			<view class="title">
				欢迎来到智洁环控！
			</view>
			<view class="little-title">
				智能垃圾管理，开启绿色未来
			</view>
		</view>

	</view>
</template>

<script setup>
	import {
		onMounted
	} from 'vue';

	function toLogin() {
		uni.navigateTo({
			url: '/pages/LoginIt'
		})
	}
	setTimeout(() => {
		toLogin()
	}, 1000)
</script>

<style>
	.content {

		background: url("../../static/background.jpg");
		background-size: cover;
		height: 100vh;
		width: 100vw;
		background-color: rgba(255, 255, 255, 0.3);
		background-position: center center;
	}

	.mask {
		display: flex;
		flex-direction: column;
		align-items: center;
		width: 100%;
		height: 100%;
		background-color: rgba(255, 255, 255, 0.5);
	}

	.logo {
		height: 300rpx;
		width: 300rpx;
		margin-top: 250rpx;
		margin-left: auto;
		margin-right: auto;
		margin-bottom: 50rpx;
	}

	.title {
		font-size: 60rpx;
		font-weight: bold;
	}

	.little-title {
		margin-top: 10%;
		font-size: 50rpx;
		font-weight: bold;
	}
</style>