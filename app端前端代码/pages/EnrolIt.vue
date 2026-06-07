<template>
	<view class="main">
		<view class="status_bar">
			<!-- 这里是状态栏 -->
		</view>
		<image src="../static/logo1.png" mode="" class="logo"></image>
		<view class="title"> 注册 </view>
		<view class="littleTitle"> 注册一个新账户 </view>
		<view class="input-box-credit">
			<image src="../static/login1.png" class="head" />
			<input placeholder="请输入手机号" class="input" v-model="credit"></input>
		</view>
		<view class="input-box-password">
			<image src="../static/code.png" class="head" />
			<input placeholder="请输入验证码" class="input" v-model="credit"></input>
			<view class="code">
				<view ref="emailMsg" @click="emailIt" :disabled="emailMsgJudge" :style="buttonStyle" class="button">
					获取验证码</view>
			</view>
		</view>
		<view class="input-box-again-one">
			<image src="../static/password.png" class="head" />
			<input placeholder="请输入账号密码" class="input" v-model="credit"></input>
		</view>
		<view class="input-box-again-two">
			<image src="../static/password.png" class="head" />
			<input placeholder="请再次输入账号密码" class="input" v-model="credit"></input>
		</view>
		<view class="button-box">
			<button class="button">注册</button>
		</view>
		<view class="enrol-box">
			<view class="word">
				记起密码？
			</view>
			<view class="enrol" @click="toHomepage">
				登录
			</view>
		</view>
	</view>
</template>

<script setup lang="ts">
	import {
		computed,
		inject,
		ref
	} from "vue";
	import {
		ID_INJECTION_KEY
	} from "element-plus";

	const idContext = inject(ID_INJECTION_KEY);
	const judge = ref(false);
	const credit = ref();
	const emailMsg = ref<HTMLElement>();
	const currentDate = ref();
	const emailMsgNum = ref<number>(60);
	const intervalId = ref<number | null>(null);
	const emailMsgJudge = ref<boolean>(false);
	const password = ref("");
	const buttonStyle = computed(() => {
		return {
			backgroundColor: emailMsgJudge.value ? "gray" : "rgba(89, 138, 199, 1)",
		};
	});

	function toForget() {
		uni.navigateTo({
			url: '/pages/ForgetPassword'
		})
	}

	function toHomepage() {
		uni.navigateTo({
			url: '/pages/LoginIt'
		})
	}
	async function emailIt() {
		emailMsg.value!.textContent = `${emailMsgNum.value}s`;

		emailMsgJudge.value = true;
		intervalId.value = Number(
			setInterval(() => {
				if (emailMsgNum.value) emailMsgNum.value--;
				emailMsg.value!.textContent = `${emailMsgNum.value}s`;
				if (emailMsgNum.value === 0) {
					clearInterval(Number(intervalId.value));
					emailMsg.value!.textContent = `发送验证码`;
					emailMsgNum.value = 60;
					emailMsgJudge.value = false;
				}
			}, 1000)
		);
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
			margin-top: 3%;

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


		.input-box-password {
			width: 75%;
			height: 5%;
			padding-left: 5%;
			display: flex;
			justify-content: flex-start;
			align-items: center;
			margin-top: 5%;

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

			.code {
				font-size: 15rpx;
				position: absolute;
				margin-left: 46%;
				width: 19%;
				height: 4%;


				.button {
					display: flex;
					align-items: center;
					margin-top: 5%;
					border-radius: 5px;
					justify-content: center;
					background-color: blue;
					color: white;
					height: 80%;
					font-size: 18rpx;
				}
			}
		}

		.input-box-again-one {
			width: 75%;
			height: 5%;
			padding-left: 5%;
			display: flex;
			justify-content: flex-start;
			align-items: center;
			margin-top: 5%;

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

		.input-box-again-two {
			width: 75%;
			height: 5%;
			padding-left: 5%;
			display: flex;
			justify-content: flex-start;
			align-items: center;
			margin-top: 5%;

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


		.button-box {
			margin-top: 5%;
			width: 30%;
			height: 5%;
			display: flex;
			align-items: center;

			.button {
				margin-top: 5%;
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
			margin-top: 3%;
			font-weight: bold;

			.enrol {
				margin-left: 25%;
				color: rgba(11, 67, 238, 1);
			}
		}
	}
</style>