<template>
	<view class="main">
		<LogoTitleVue></LogoTitleVue>
		<view class="time">
			<view class="word">
				查询时间段
			</view>
			<uni-datetime-picker v-model="range" type="daterange" @maskClick="maskClick" class="time-choose" />

		</view>
		<view class="bin-code">
			<view class="word">
				垃圾桶编号
			</view>
			<input type="text" placeholder="请输入垃圾桶编号" class="bin-choose" v-model="bin_id" />
		</view>
		<view class="query-button">
			<button class="button" @click="getEvent">查询</button>
		</view>
		<view class="icon-box">
			<image src="../static/warnTip.png" mode="" class="img"></image>
			<view class="word">
				垃圾已满
			</view>
			<image src="../static/smokeWarn.png" mode="" class="img"></image>
			<view class="word">
				烟雾报警
			</view>
			<image src="../static/fix.png" mode="" class="img"></image>
			<view class="word">
				需要维修
			</view>
		</view>
		<view class="white-box">
			<view class="top-title">
				<view class="word">
					{{currentDate}}
				</view>
				<view>
					<view class="reset" @click="getEvent">刷新</view>
				</view>
			</view>
			<scroll-view :scroll-top="0" scroll-y="true" class="scroll" @scroll="scroll">
				<view class="list-body" v-for='(item, index) in mainData' :key="mainData.event_id">
					<view class="content">
						<view class="line">
							<view class="prev">
								垃圾桶编号：
							</view>
							<view>
								{{item.bin_id}}
							</view>
						</view>
						<view class="line">
							<view class="prev">
								垃圾桶状态：
							</view>
							<image src="../static/warnTip.png" mode="" class="img" v-show="'已满'==item.status"></image>
							<image src="../static/smokeWarn.png" mode="" class="img" v-show="'报警'==item.status"></image>
							<image src="../static/fix.png" mode="" class="img" v-show="'维修'==item.status"></image>
						</view>
						<view class="line">
							<view class="prev">
								筛选方式：
							</view>
							<view>
								{{item.trigger}}
							</view>
						</view>
						<view class="line">
							<view class="prev">
								创建时间：
							</view>
							<view>
								{{item.event_time}}
							</view>
						</view>
					</view>
					<view class="detail-box">
						<view class="detail" @click="showPhoto(item.status)">详情</view>
						<view class="del" @click="deleteAndRe(item.event_id)">删除</view>
					</view>
				</view>
			</scroll-view>
		</view>
		<view class="photo" v-show="isPhoto" @click="disappearPhoto">
			<view class="photo-box">
				<image :src=imageSrc mode="" class="img"></image>
			</view>
		</view>
		<view class="mask-box" v-show="showDelete">
			<view class="quit-box">
				<view class="title-box">
					<image src="../static/warnTip.png" mode="" class="img"></image>
					<view class="tip">
						提示
					</view>
				</view>
				<view class="word">
					您确定要删除吗？
				</view>
				<view class="word-again">
					删除后内容不再保存！
				</view>
				<view class="button-box">
					<view class="button-left" @click="deleteEvent">
						确定
					</view>
					<view class="button-right" @click="disappear">
						取消
					</view>
				</view>
			</view>
		</view>
	</view>

</template>

<script setup lang="ts">
	import { ref } from 'vue';
	import LogoTitleVue from './LogoTitle.vue';
	let range = [];
	const mainData = ref<any>([])
	const imageSrc = ref<String>();
	const showDelete = ref();
	const event_id = ref();
	const currentDate = ref();
	const imgBox = ref([
		"/static/allFull1.jpg", "/static/badBin.jpg", "/static/smoke1.jpg"
	]);
	const isPhoto = ref(false);
	const token = uni.getStorageSync('token');
	function showPhoto(status : String) {
		if (status == "已满") {
			imageSrc.value = imgBox.value[0];
		}

		else if (status == "报警") {
			imageSrc.value = imgBox.value[2];
		}

		else {
			imageSrc.value = imgBox.value[1];
		}
		isPhoto.value = true
	}
	function disappearPhoto() {
		isPhoto.value = false
	}
	function disappear() {
		showDelete.value = false;
	}
	function getCurrentDate() {
		const date = new Date();
		const year = date.getFullYear();
		const month = (date.getMonth() + 1).toString().padStart(2, '0');
		const day = date.getDate().toString().padStart(2, '0');
		currentDate.value = `${year}-${month}-${day}`;
	}
	getCurrentDate()
	function maskClick(e) {
		console.log('maskClick事件:', e);
	}
	function scroll(e) {
		// console.log(e)
		// this.old.scrollTop = e.detail.scrollTop
	}
	const bin_id = ref();
	function deleteAndRe(id : Number) {
		event_id.value = id;
		showDelete.value = true;
	}
	async function getEvent() {

		uni.request({
			url: 'https://trash.sipc115.com/api/data/event',
			method: 'POST',
			header: {
				'Authorization': token,
			},
			data: {
				"cluster_id": uni.getStorageSync('clusterId'),
				"bin_id": bin_id.value,
				"status": "",
				"trigger": "",
				"start_time": range[0] || '',
				"end_time": range[1] || '',
			},
			success: (res) => {
				mainData.value = res.data.data;
				console.log(res.data);
			},
		});
	}
	async function deleteEvent() {
		showDelete.value = false;
		uni.request({
			url: `https://trash.sipc115.com/api/data/event/${event_id.value}`,
			method: 'DELETE',
			header: {
				'Authorization': token,
			},
			success: (res) => {
				console.log(res.data);
				getEvent();
			},
		});

	}
	getEvent()
</script>

<style lang="scss" scoped>
	.main {
		width: 100vw;
		background-color: rgba(228, 246, 200, 0.61);
		margin: 0;
		padding: 0;
		height: 100vh;

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

			.word-again {
				display: flex;
				justify-content: center;
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

		.photo {
			position: absolute;
			top: 0;
			left: 0;
			width: 100%;
			height: 100%;
			background-color: transparent;
			display: flex;
			align-items: center;
			justify-content: center;

			.photo-box {
				width: 90%;
				height: 30%;
				border-radius: 25rpx;

				.img {
					width: 100%;
					height: 100%;
				}
			}
		}

		.time {
			display: flex;
			width: 100%;
			align-items: center;
			margin-top: 5%;
			height: 5%;

			.word {
				margin-left: 5%;
				font-size: 35rpx;
				color: rgba(78, 89, 105, 1);
			}

			.time-choose {
				height: 100%;
				background-color: white;
				margin-left: 5%;
				margin-right: 10%;
				font-size: 25rpx;
				flex: 1;
				color: rgba(136, 136, 136, 1);
			}
		}

		.bin-code {
			display: flex;
			width: 100%;
			align-items: center;
			margin-top: 5%;
			height: 5%;

			.word {
				margin-left: 5%;
				font-size: 35rpx;
				color: rgba(78, 89, 105, 1);
			}

			.bin-choose {
				height: 100% !important;
				color: rgba(136, 136, 136, 1);
				background-color: white;
				flex: 1;
				font-size: 25rpx;
				margin-left: 5%;
				margin-right: 10%;
				padding-left: 5%;
			}
		}

		.query-button {
			width: 50%;
			margin-left: 25%;
			height: 80rpx;
			margin-top: 5%;

			.button {
				height: 100%;
				width: 100%;
				font-size: 35rpx;
				font-weight: bold;
				color: white;
				display: flex;
				align-items: center;
				justify-content: center;
				background-color: rgb(86, 119, 34);
			}
		}

		.icon-box {
			display: flex;
			justify-content: space-around;
			align-items: center;
			margin-top: 5%;
			margin-left: 5%;
			margin-right: 5%;

			.img {
				width: 60rpx;
				height: 60rpx;
			}

			.word {
				font-size: 30rpx;
				font-weight: bold;
			}
		}

		.white-box {
			width: 90%;
			margin-left: 5%;
			background-color: white;
			height: 50%;

			.top-title {
				height: 18%;
				width: 90%;
				display: flex;
				margin-top: 5%;
				justify-content: space-between;
				align-items: center;
				margin-left: 5%;
				margin-right: 5%;

				.reset {
					background-color: rgb(247, 248, 250);
					margin-top: 5%;
					width: 120rpx;
					height: 50rpx;
					display: flex;
					align-items: center;
					justify-content: center;
					color: rgb(78, 89, 105);
				}
			}

			.scroll {
				height: 75%;

				.list-body {
					margin-top: 5%;
					margin-left: 3%;
					width: 94%;
					height: 30%;
					display: flex;
					justify-content: space-between;
					border-radius: 5px;
					box-shadow: 0 4rpx 10rpx rgba(0, 0, 0, 0.5);

					.content {
						font-size: 25rpx;
						margin-top: 3%;
						margin-bottom: 3%;
						margin-left: 3%;

						.line {
							display: flex;
							align-items: center;

							.img {
								width: 40rpx;
								height: 40rpx;
							}

							.prev {
								font-weight: bold;
							}
						}

					}

					.detail-box {
						margin-right: 5%;
						display: flex;
						flex-direction: column;
						justify-content: space-around;
						align-items: center;

						.detail {
							width: 130rpx;
							height: 65rpx;
							background-color: rgb(214, 242, 168);
							display: flex;
							align-items: center;
							justify-content: center;
							color: rgb(78, 89, 105);
						}

						.del {
							width: 130rpx;
							height: 65rpx;
							background-color: rgb(247, 248, 250);
							display: flex;
							align-items: center;
							justify-content: center;
							color: rgb(78, 89, 105);
						}
					}
				}
			}
		}
	}
</style>