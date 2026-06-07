<template>
	<view class="main">
		<view class="title">
			<view class="img-box">
				<image src="../static/logo.png" mode="" class="logo"></image>
				<view class="word">
					智洁环控
				</view>
			</view>
		</view>
		<view class="person-body">
			<view class="avatar-box">
				<image src="" mode="" class="avatar"></image>
				<view class="button">修改个人信息</view>
			</view>

			<view class="body">
				<view class="name-box">
					<view class="name">
						宣宣
					</view>
					<view class="status-word">
						实名认证：
					</view>
					<view class="status">
						已认证
					</view>
				</view>
				<view class="message-box">
					工号：123456
				</view>
				<view class="message-box">
					邮箱：3462079334@qq.com
				</view>
				<view class="message-box">
					手机号码：1234567891231
				</view>
				<view class="message-box">
					注册时间：2024-08-02
				</view>
			</view>
		</view>
		<view class="end-part">
			<view class="line" @click="showAboutUs">
				<image src="../static/aboutUs.png" mode="" class="img"></image>
				<view class="word">
					关于我们
				</view>
			</view>
			<view class="line" @click="showRebackBox">
				<image src="../static/reback.png" mode="" class=" img"></image>
				<view class="word">
					意见反馈
				</view>
			</view>
			<view class="line" @click="showQuitBox">
				<image src="../static/battery.png" mode="" class="img"></image>
				<view class="word" style="color: red;">
					退出登录
				</view>
			</view>
		</view>
		<view class="mask-box" v-show="judgeAboutUs">
			<view class="about-us">
				<view class="title">
					关于我们
				</view>
				<view class="little-title">
					开发团队：发际线和我作队
				</view>
				<view class="little-title">
					开发人员：lxt，yhy，wyn，wyh，lsz
				</view>
				<view class="little-title">
					联系方式：3462079334（QQ）
				</view>
				<view class="little-title">
					版本号：V1.0.0
				</view>
				<view class="button-box">
					<view class="button" @click="disappearAboutUs">
						确认
					</view>
				</view>
			</view>

		</view>
		<view class="mask-box" v-show="judgeRebackBox">
			<view class="reback-box">
				<view class="word">
					您对“智洁环控”有什么意见、建议，或者发现了什么bug都可以反馈给我们
				</view>
				<textarea placeholder="请输入" class="input" />
				<view class="button-box">
					<view class="button" @click="disappearRebackBox">
						提交
					</view>
				</view>
			</view>
		</view>
		<view class="mask-box" v-show="judgeQuitBox">
			<view class="quit-box">
				<view class="title-box">
					<image src="../static/warnTip.png" mode="" class="img"></image>
					<view class="tip">
						提示
					</view>
				</view>
				<view class="word">
					您确定要退出登录吗？
				</view>
				<view class="button-box">
					<view class="button-left" @click="toHomepage">
						确定
					</view>
					<view class="button-right" @click="disappearQuitBox">
						取消
					</view>
				</view>
			</view>
		</view>

	</view>

</template>

<script setup lang="ts">
	import { ref } from 'vue';
	const judgeAboutUs = ref(false)
	const judgeRebackBox = ref(false)
	const judgeQuitBox = ref(false)
	function showAboutUs() {
		judgeAboutUs.value = true;
	}
	function showRebackBox() {
		judgeRebackBox.value = true
	}
	function showQuitBox() {
		judgeQuitBox.value = true
	}
	function disappearAboutUs() {
		judgeAboutUs.value = false;
	}
	function disappearRebackBox() {
		judgeRebackBox.value = false;
	}
	function disappearQuitBox() {
		judgeQuitBox.value = false;
	}
	function toHomepage() {
		uni.navigateTo({
			url: '/pages/LoginIt'
		})
	}
</script>

<style scoped lang="scss">
	.main {
		width: 100vw;
		height: 100vh;
		background-color: rgba(228, 246, 200, 0.61);
		margin: 0;
		padding: 0;

		.mask-box {
			position: absolute;
			background-color: rgba(255, 255, 255, 0.3);
			width: 100%;
			height: 100%;
			top: 0;
			left: 0;
		}

		.quit-box {
			position: absolute;
			top: 50%;
			left: 50%;
			transform: translate(-50%, -50%);
			background-color: white;
			width: 70%;
			height: 30%;

			.title-box {
				display: flex;
				align-items: center;
				margin-top: 3%;
				margin-left: 5%;
				width: 100%;

				.img {
					width: 60rpx;
					height: 60rpx;
				}

				.tip {
					margin-left: 5%;
					font-size: 35rpx;
					font-weight: bold;
					color: rgba(130, 129, 129, 1);
				}

			}

			.word {
				display: flex;
				justify-content: center;
				margin-top: 15%;
				font-size: 35rpx;
			}

			.button-box {
				margin-top: 15%;
				display: flex;
				justify-content: space-around;
				height: 15%;
				width: 100%;

				.button-left {
					display: flex;
					align-items: center;
					justify-content: center;
					background-color: rgba(64, 91, 20, 1);
					color: white;
					border-radius: 5px;
					width: 30%;
					height: 100%;
				}

				.button-right {
					display: flex;
					align-items: center;
					justify-content: center;
					border-radius: 5px;
					width: 30%;
					height: 100%;
					border: 1px solid gray;
				}
			}
		}

		.reback-box {
			position: absolute;
			top: 50%;
			left: 50%;
			transform: translate(-50%, -50%);
			background-color: white;
			width: 70%;
			height: 30%;

			.word {
				display: flex;
				justify-content: center;
				margin-top: 3%;
				margin-left: 3%;
				width: 94%;
				font-size: 28rpx;
				font-weight: bold;
			}

			.input {
				margin-top: 5%;
				margin-left: 5%;
				width: 90%;
				border: 1rpx solid black;
				height: 50%;
			}

			.button-box {
				display: flex;
				justify-content: center;
				align-items: center;
				margin-top: 5%;
				height: 13%;

				.button {
					display: flex;
					align-items: center;
					justify-content: center;
					background-color: rgba(64, 91, 20, 1);
					color: white;
					border-radius: 5px;
					width: 30%;
					height: 100%;
				}
			}
		}


		.about-us {
			position: absolute;
			top: 50%;
			left: 50%;
			transform: translate(-50%, -50%);
			background-color: white;
			width: 70%;
			height: 30%;


			.title {
				display: flex;
				justify-content: center;
				margin-top: 1%;
				font-size: 35rpx;
				font-weight: bold;
			}

			.little-title {
				display: flex;
				justify-content: center;
				margin-top: 5%;
				font-size: 30rpx;
			}

			.button-box {
				display: flex;
				justify-content: center;
				align-items: center;
				margin-top: 5%;
				height: 13%;

				.button {
					display: flex;
					align-items: center;
					justify-content: center;
					background-color: rgba(64, 91, 20, 1);
					color: white;
					border-radius: 5px;
					width: 30%;
					height: 100%;
				}
			}
		}

		.title {
			display: flex;
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
			}

			.word {
				font-size: 35rpx;
				color: rgba(86, 119, 34, 1);
				font-weight: bold;
			}
		}

		.person-body {
			display: flex;
			margin-top: 5%;
			margin-left: 8%;

			.avatar-box {
				display: flex;
				flex-direction: column;
				align-items: center;

				.avatar {
					border-radius: 50%;
					height: 180rpx;
					width: 180rpx;
					background-color: white;
				}

				.button {
					margin-top: 8%;
					width: 110%;
					height: 20%;
					background-color: rgb(247, 248, 250);
					display: flex;
					align-items: center;
					justify-content: center;
					border-radius: 5px;
				}
			}


			.body {
				margin-left: 10%;
				font-size: 25rpx;
				flex: 1;

				.message-box {
					margin-top: 3%;
				}

				.name-box {
					margin-top: 3%;
					display: flex;
					align-items: center;

					.name {
						font-size: 35rpx;

					}

					.status-word {
						margin-left: 5%;
					}

					.status {
						width: 130rpx;
						height: 50rpx;
						font-size: 18rpx;
						display: flex;
						align-items: center;
						justify-content: center;
						background-color: rgb(232, 255, 234);
						color: rgba(45, 194, 79, 1);
					}
				}
			}
		}

		.end-part {
			margin-top: 5%;

			.line {
				height: 120rpx;
				background-color: white;
				border-radius: 25px;
				width: 80%;
				margin-left: 10%;
				margin-top: 7%;
				box-shadow: 0 4rpx 10rpx rgba(0, 0, 0, 0.5);
				display: flex;
				align-items: center;

				.img {
					margin-left: 5%;
					width: 80rpx;
					height: 80rpx;
				}

				.word {
					margin-left: 25%;
				}
			}
		}
	}
</style>