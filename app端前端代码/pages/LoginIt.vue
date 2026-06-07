<template>
	<view class="main">
		<view class="status_bar">
			<!-- 这里是状态栏 -->
		</view>
		<image src="../static/logo1.png" mode="" class="logo"></image>
		<view class="title"> 登录 </view>
		<view class="littleTitle"> 账号密码登录 </view>
		<view class="input-box-credit">
			<image src="../static/login1.png" class="head" />
			<input placeholder="请输入工号" class="input" v-model="account"></input>
		</view>
		<view class="credit-box">
			<view class="error">

				<image src="../static/warnTip.png" class="error-photo" v-show="judge" />
				<view v-show="judge">工号错误</view>

			</view>
		</view>
		<view class="input-box-password">
			<image src="../static/password.png" class="head" />
			<input placeholder="请输入密码" class="input" v-model="password" type="password"></input>
		</view>
		<view class="password-box">
			<view class="error" style="">
				<image src="../static/warnTip.png" class="error-photo" v-show="judge" />
				<view v-show="judge">密码错误</view>
				<view class="forget" @click="toForget">
					忘记密码
				</view>
			</view>
		</view>
		<view class="button-box">
			<button class="button" @click="toMain">登录</button>
		</view>
		<view class="enrol-box">
			<view class="word">
				没有账号？
			</view>
			<view class="enrol" @click="toEnrol">
				注册
			</view>
		</view>
	</view>
</template>

<script setup>
	import {
		inject,
		ref
	} from "vue";
	import {
		ID_INJECTION_KEY
	} from "element-plus";

	const idContext = inject(ID_INJECTION_KEY);
	const judge = ref(false);
	const account = ref();
	const password = ref();

	function toForget() {
		uni.navigateTo({
			url: '/pages/ForgetPassword'
		})
	}

	function toEnrol() {
		uni.navigateTo({
			url: '/pages/EnrolIt'
		})
	}

	function toMain() {
		judge.value = false;
		uni.request({
			url: 'https://trash.sipc115.com/api/user/login',
			method: 'POST',
			data: {
				account: account.value,
				password: password.value
			},
			success: (res) => {
				if (res.data.code != "00000") {
					judge.value = true;
				}
				console.log(res.data);
				uni.setStorageSync('token', res.data.data.token)
				uni.switchTab({
					url: '/pages/DataAnalyse'
				})
			},
		});
	}
</script>

<style lang="scss">
	.main {
		width: 100vw;
		height: 100vh;
		background-color: rgba(228, 246, 200, 0.61);
		display: flex;
		align-items: center;
		flex-direction: column;

		.status_bar {
			height: var(--status-bar-height);
			width: 100%;
			background-color: white;
		}

		.logo {
			margin-top: 20%;
			width: 350rpx;
			height: 350rpx;
		}

		.title {
			font-size: 60rpx;
			font-weight: bold;
		}

		.littleTitle {
			margin-top: 1%;
			font-size: 50rpx;
			font-weight: bold;
		}

		.input-box-credit {
			width: 75%;
			height: 5%;
			padding-left: 5%;
			display: flex;
			justify-content: flex-start;
			align-items: center;
			margin-top: 10%;

			.head {
				margin-left: 5%;
				width: 70rpx;
				height: 70rpx;
			}

			.input {
				margin-left: 10%;
				width: 55%;
				height: 100%;
				border-radius: 5%;
				font-weight: bold;
				font-size: 25rpx;
				background-color: white;
				padding-left: 5%;
			}
		}

		.credit-box {
			width: 45%;
			height: 6%;
			margin-left: 15%;
			display: flex;

			.error {
				display: flex;
				align-items: center;
				font-size: 25rpx;
				color: rgba(233, 17, 17, 0.55);

				.error-photo {
					width: 50rpx;
					height: 50rpx;
				}
			}
		}

		.input-box-password {
			width: 75%;
			height: 5%;
			padding-left: 5%;
			display: flex;
			justify-content: flex-start;
			align-items: center;

			.head {
				margin-left: 5%;
				width: 70rpx;
				height: 70rpx;
			}

			.input {
				margin-left: 10%;
				width: 55%;
				height: 100%;
				border-radius: 5%;
				font-weight: bold;
				font-size: 25rpx;
				background-color: white;
				padding-left: 5%;
			}
		}

		.password-box {
			width: 45%;
			height: 6%;
			margin-left: 15%;
			display: flex;

			.error {
				display: flex;
				align-items: center;
				font-size: 25rpx;
				color: rgba(233, 17, 17, 0.55);

				.error-photo {
					width: 50rpx;
					height: 50rpx;
				}
			}

			.forget {
				font-size: 35rpx;
				position: absolute;
				margin-left: 25%;
				font-weight: bold;
				color: rgba(11, 67, 238, 1);
			}
		}

		.button-box {
			margin-top: 10%;
			width: 30%;
			height: 5%;
			display: flex;
			align-items: center;

			.button {
				font-size: 30rpx;
				width: 100%;
				height: 100%;
				background-color: rgb(208, 225, 133);
				color: white;
			}
		}

		.enrol-box {
			display: flex;
			font-size: 25rpx;
			width: 32%;
			margin-top: 2%;
			font-weight: bold;

			.enrol {
				margin-left: 25%;
				color: rgba(11, 67, 238, 1);
			}
		}
	}
</style>