<template>
	<view class="main">
		<!-- <LogoTitleVue></LogoTitleVue> -->
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
		<view class="title-line">
			未来&nbsp;<text class="word">5</text>&nbsp;天预测
		</view>
		<view class="ico">
			<image src="../static/warnTip.png" mode="" class="photo"></image>
			<view class="word">
				&nbsp;危险预测&nbsp;
			</view>
			<image src="../static/warnTip.png" mode="" class="photo"></image>
		</view>
		<view class="white-box">
			<view class="item">
				<view class="word">
					根据数据分析未来3天内边村甲烷数有<text>超标</text>的可能，请负责人员重点关注！
				</view>
				<view class="body">
					<swiper class="swiper" circular :indicator-dots="true" :autoplay="true" :interval="2000"
						:duration="500">
						<swiper-item>
							<image src="../static/jw.jpg" mode="" class="photo"></image>
						</swiper-item>
						<swiper-item>
							<image src="../static/jw2.jpg" mode="" class="photo"></image>
						</swiper-item>
					</swiper>
					<view class="progress">
						<qiun-data-charts type="arcbar" :opts="optsLineFirst" :chartData="chartDataFirst" />

					</view>
				</view>
			</view>
			<view class="item">
				<view class="word">
					根据数据分析御溪园社区06号垃圾桶常有<text>烟雾报警</text>，请负责人员重点关注

				</view>
				<view class="body">
					<swiper class="swiper" circular :indicator-dots="true" :autoplay="true" :interval="2000"
						:duration="500">
						<swiper-item>
							<image src="../static/smoke2.jpg" mode="" class="photo"></image>
						</swiper-item>
						<swiper-item>
							<image src="../static/smoke1.jpg" mode="" class="photo"></image>
						</swiper-item>
					</swiper>
					<view class="progress">
						<qiun-data-charts type="arcbar" :opts="optsLineSecond" :chartData="chartDataSecond" />
					</view>
				</view>
			</view>
			<view class="item-end">
				<view class="word">
					天津理工大学集群05号桶出现<text>溢出破损</text>，请相关人员及时收取垃圾和维修垃圾桶

				</view>
				<view class="body">
					<swiper class="swiper" circular :indicator-dots="true" :autoplay="true" :interval="2000"
						:duration="500">
						<swiper-item>
							<image src="../static/allFull1.jpg" mode="" class="photo"></image>
						</swiper-item>
						<swiper-item>
							<image src="../static/allFull2.jpg" mode="" class="photo"></image>
						</swiper-item>

					</swiper>
					<view class="progress">
						<qiun-data-charts type="arcbar" :opts="optsLineThird" :chartData="chartDataThird" />
					</view>
				</view>
			</view>
		</view>
		<!-- <TrashDataVue></TrashDataVue> -->
		<view class="open-times-title">
			总开盖次数
		</view>
		<view class="open-times-photo">
			<view style="display: flex;width: 40%;">
				<image src="../static/bin.png" mode="" class="bin-photo"></image>
				<view class="number-bin">
					<view class="times-title">
						日开盖次数
					</view>
					<view class="times">
						{{totalTimes}}次
					</view>
				</view>
			</view>
			<view style="display: flex;width: 40%;">
				<image src="../static/profit.png" mode="" class="line-photo"></image>
				<view class="number-line">
					<view class="times-title">
						较昨日变化
					</view>
					<view class="times">
						{{rate}}%
					</view>
				</view>
			</view>
		</view>
		<view class="photo-top">
			<view class="first-word">
				开盖次数
			</view>
			<view class="second-word">
				（近五日）
			</view>
		</view>
		<view class="open-chart">
			<qiun-data-charts type="line" :opts="opts" :chartData="chartData" :optsWatch="false" />
		</view>
		<view class="open-times-title">
			数据总览
		</view>
		<view class="tip">
			单位：件
		</view>
		<view class="classify">
			<view class="item">
				<view class="detail">
					<view class="word">
						有害垃圾
					</view>
					<view class="sum">
						<image src="../static/dangerTrash.png" mode="" class="photo"></image>
						<view style="font-weight: bold;width: 5%;font-size: 35rpx;margin-left: 2%;">
							{{diffData[0]}}
						</view>
					</view>

				</view>
				<view class="detail">
					<view class="word">
						厨余垃圾
					</view>
					<view class="sum">
						<image src="../static/foodWaste2.png" mode="" class="photo"></image>
						<view style="font-weight: bold;width: 5%;font-size: 35rpx;margin-left: 2%;">
							{{diffData[1]}}
						</view>
					</view>

				</view>
			</view>
			<view class="item">
				<view class="detail" style="margin-top: 3%;">
					<view class="word">
						可回收物
					</view>
					<view class="sum">
						<image src="../static/recycleTrash.png" mode="" class="photo"></image>
						<view style="font-weight: bold;width: 5%;font-size: 35rpx;margin-left: 2%;">
							{{diffData[2]}}
						</view>
					</view>
				</view>
				<view class="detail" style="margin-top: 3%;">
					<view class="word">
						其他垃圾
					</view>
					<view class="sum">
						<image src="../static/otherTrash.png" mode="" class="photo"></image>
						<view style="font-weight: bold;width: 5%;font-size: 35rpx;margin-left: 2%;">
							{{diffData[3]}}
						</view>
					</view>

				</view>
			</view>
		</view>
		<view class="data-chart">
			<qiun-data-charts type="area" :opts="dataOpts" :chartData="dataChartData" :optsWatch="false" />
		</view>
	</view>
</template>

<script setup lang="ts">
	import LogoTitleVue from './LogoTitle.vue';
	import { ref, watch } from 'vue';
	const optsLineFirst = {
		color: ["#405b14", "#FC8452", "#9A60B4", "#ea7ccc"],
		padding: undefined,
		title: {
			name: "58%",
			fontSize: 25,
			color: "#405b14"
		},
		subtitle: {
			name: "",
			fontSize: 25,
			color: "#666666"
		},
		extra: {
			arcbar: {
				type: "circle",
				width: 10,
				backgroundColor: "#E9E9E9",
				startAngle: 1.5,
				endAngle: 0.25,
				gap: 2
			}
		}
	}
	let resLineFirst = {
		series: [
			{
				name: "正确率",
				color: "#405b14",
				data: 0.58
			}
		]
	};
	let chartDataFirst = JSON.parse(JSON.stringify(resLineFirst));
	const optsLineSecond = {
		color: ["#405b14", "#FC8452", "#9A60B4", "#ea7ccc"],
		padding: undefined,
		title: {
			name: "79%",
			fontSize: 25,
			color: "#405b14"
		},
		subtitle: {
			name: "",
			fontSize: 25,
			color: "#666666"
		},
		extra: {
			arcbar: {
				type: "circle",
				width: 10,
				backgroundColor: "#E9E9E9",
				startAngle: 1.5,
				endAngle: 0.25,
				gap: 2
			}
		}
	}
	let resLineSecond = {
		series: [
			{
				name: "正确率",
				color: "#405b14",
				data: 0.79
			}
		]
	};
	let chartDataSecond = JSON.parse(JSON.stringify(resLineSecond));

	const optsLineThird = {
		color: ["#405b14", "#FC8452", "#9A60B4", "#ea7ccc"],
		padding: undefined,
		title: {
			name: "75%",
			fontSize: 25,
			color: "#405b14"
		},
		subtitle: {
			name: "",
			fontSize: 25,
			color: "#666666"
		},
		extra: {
			arcbar: {
				type: "circle",
				width: 10,
				backgroundColor: "#E9E9E9",
				startAngle: 1.5,
				endAngle: 0.25,
				gap: 2
			}
		}
	}
	let resLineThird = {
		series: [
			{
				name: "正确率",
				color: "#405b14",
				data: 0.75
			}
		]
	};
	let chartDataThird = JSON.parse(JSON.stringify(resLineThird));
	const totalTimes = ref();
	const rate = ref();
	const diffData = ref([]);
	const options = ref();
	const array = ref(['天津理工大学', '美国', '巴西', '日本'])
	const index = ref(0);
	const cluster_id = ref(3)
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
	let res = {
		categories: ["2018", "2019", "2020", "2021", "2022", "2023"],
		series: [
			{
				name: "总开盖次数",
				linearColor: [
					[
						0,
						"#1890FF"
					],
					[
						0.25,
						"#00B5FF"
					],
					[
						0.5,
						"#00D1ED"
					],
					[
						0.75,
						"#00E6BB"
					],
					[
						1,
						"#90F489"
					]
				],
				setShadow: [
					3,
					8,
					10,
					"#1890FF"
				],
				data: []
			},
		]
	};
	const chartData = ref({});
	chartData.value = JSON.parse(JSON.stringify(res))
	const opts = {
		color: ["#1890FF", "#91CB74", "#FAC858", "#EE6666", "#73C0DE", "#3CA272", "#FC8452", "#9A60B4", "#ea7ccc"],
		padding: [],
		dataLabel: false,
		dataPointShape: false,
		enableScroll: false,
		legend: {},
		xAxis: {
			disableGrid: true
		},
		yAxis: {
			gridType: "dash",
			dashLength: 2
		},
		extra: {
			line: {
				type: "curve",
				width: 2,
				activeType: "hollow",
				linearType: "custom",
				onShadow: true,
				// animation: "horizontal"
			},
		}
	}
	let dataChartData = ref({})
	const dataOpts = {
		color: ["#1890FF", "#91CB74", "#EE6666", "#9A60B4"],
		padding: [15, 15, 0, 15],
		enableScroll: false,
		legend: {},
		xAxis: {
			disableGrid: true
		},
		yAxis: {
			gridType: "dash",
			dashLength: 2
		},
		extra: {
			area: {
				type: "curve",
				opacity: 0.2,
				addLine: true,
				width: 2,
				gradient: true,
				activeType: "hollow"
			}
		}
	}
	let dataRes = {
		categories: ["2018", "2019", "2020", "2021", "2022", "2023"],
		series: [
			{
				name: "可回收物",
				data: []
			},
			{
				name: "厨余垃圾",
				data: []
			},
			{
				name: "有害垃圾",
				data: []
			},
			{
				name: "其他垃圾",
				data: []
			}
		]
	};
	dataChartData.value = JSON.parse(JSON.stringify(dataRes));
	async function getDataTimes() {
		cluster_id.value = uni.getStorageSync('clusterId')
		uni.request({
			url: `https://trash.sipc115.com/api/data/cluster/${cluster_id.value || 3}/rubbish`,
			method: 'GET',
			header: {
				'Authorization': token,
			},
			success: (response) => {
				console.log(response.data);
				dataRes.categories = response.data.data.date;
				dataRes.series[0].data = response.data.data.recyclable_count;
				diffData.value[0] = response.data.data.recyclable_count[4];
				dataRes.series[1].data = response.data.data.food_waste_count;
				diffData.value[1] = response.data.data.food_waste_count[4];
				dataRes.series[2].data = response.data.data.hazardous_waste_count;
				diffData.value[2] = response.data.data.hazardous_waste_count[4];
				dataRes.series[3].data = response.data.data.residual_waste_count;
				diffData.value[3] = response.data.data.residual_waste_count[4];
				dataChartData.value = JSON.parse(JSON.stringify(dataRes));
			}
		});
	}
	getDataTimes()
	async function getOpenTimes() {
		cluster_id.value = uni.getStorageSync('clusterId')
		uni.request({
			url: `https://trash.sipc115.com/api/data/cluster/${cluster_id.value || 3}/lid`,
			method: 'GET',
			header: {
				'Authorization': token,
			},
			success: (response) => {
				console.log(response.data);
				totalTimes.value = response.data.data.count[4];
				rate.value =
					(response.data.data.count[4] - response.data.data.count[3]) /
					response.data.data.count[4];
				rate.value = Number(rate.value.toFixed(1));
				res.categories = response.data.data.date;
				res.series[0].data = response.data.data.count;
				chartData.value = JSON.parse(JSON.stringify(res))
				// chartData = JSON.parse(JSON.stringify(res))
			}
		});
	}
	getOpenTimes()
	watch(cluster_id, () => {
		getOpenTimes()
		getDataTimes()
	})
</script>

<style scoped lang="scss">
	.main {
		width: 100vw;
		background-color: rgba(228, 246, 200, 0.61);
		margin: 0;
		padding: 0;

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

		.title-line {
			display: flex;
			justify-content: center;
			align-items: baseline;
			font-size: 35rpx;
			font-weight: bold;

			.word {
				font-size: 60rpx;
				color: rgb(64, 91, 20);
			}
		}

		.ico {
			display: flex;
			justify-content: center;
			align-items: center;
			margin-top: 3%;

			.photo {
				width: 60rpx;
				height: 60rpx;
			}

			.word {
				font-weight: bold;
			}
		}

		.white-box {
			background-color: white;
			box-shadow: 0 4rpx 10rpx rgba(0, 0, 0, 0.5);
			border-radius: 5%;
			margin-left: 5%;
			width: 90%;
			height: 90vh;

			.item-end {
				height: 33.3%;

				.word {
					width: 90%;
					margin-left: 5%;
					padding-top: 3%;
					color: rgba(54, 107, 25, 0.8);

					text {
						color: rgba(233, 17, 17, 0.78);
						font-size: 35rpx;
						font-weight: bold;
					}
				}

				.body {
					display: flex;
					align-items: center;


					.swiper {
						width: 60%;

						.photo {
							border-radius: 5%;
							width: 90%;
							margin-left: 5%;
							margin-top: 3%;
							height: 250rpx;
						}
					}

					.progress {
						width: 30%;
						margin-left: 5%;
						height: 20vh;
					}
				}
			}

			.item {
				border-bottom: 1px dotted black;
				height: 33.3%;

				.word {
					width: 90%;
					margin-left: 5%;
					padding-top: 3%;
					color: rgba(54, 107, 25, 0.8);

					text {
						color: rgba(233, 17, 17, 0.78);
						font-size: 35rpx;
						font-weight: bold;
					}
				}

				.body {
					display: flex;
					align-items: center;


					.swiper {
						width: 60%;

						.photo {
							border-radius: 5%;
							width: 90%;
							margin-left: 5%;
							margin-top: 3%;
							height: 250rpx;
						}
					}

					.progress {
						width: 30%;
						margin-left: 5%;
						height: 20vh;
					}
				}
			}
		}

		.open-times-title {
			display: flex;
			justify-content: center;
			font-weight: bold;
			padding-top: 5%;
		}

		.open-times-photo {
			display: flex;
			margin-left: 5%;
			margin-top: 8%;
			justify-content: space-between;

			.bin-photo {
				width: 80rpx;
				height: 80rpx;
			}

			.number-bin {
				margin-left: 3%;
				font-weight: bold;

				.times-title {
					font-size: 20rpx;
				}

				.times {
					font-size: 35rpx;
					margin-top: 10%;
				}
			}

			.line-photo {
				width: 80rpx;
				height: 80rpx;
			}

			.number-line {
				margin-left: 3%;
				font-weight: bold;

				.times-title {
					font-size: 20rpx;
				}

				.times {
					font-size: 35rpx;
					margin-top: 10%;
				}
			}
		}

		.photo-top {
			display: flex;
			align-items: baseline;
			margin-top: 15%;
			margin-left: 5%;

			.first-word {
				font-weight: bold;
			}

			.second-word {

				font-size: 18rpx;
			}
		}

		.open-chart {
			margin-top: 5%;
			background-color: white;
			box-shadow: 0 4rpx 10rpx rgba(0, 0, 0, 0.5);
			border-radius: 5%;
			margin-left: 5%;
			width: 90%;
			height: 30vh;
		}

		.tip {
			position: absolute;
			right: 8%;
			font-size: 25rpx;
		}

		.classify {
			display: flex;
			height: 25%;
			flex-direction: column;
			padding-top: 3%;

			.item {
				display: flex;
				justify-content: space-around;
				margin-left: 5%;
				margin-right: 5%;
				margin-top: 5%;

				.detail {


					.word {
						font-size: 20rpx;
						font-weight: bold;
					}

					.sum {
						display: flex;
						align-items: center;
						margin-top: 10%;

						.photo {
							width: 65rpx;
							height: 65rpx;
						}
					}

				}
			}
		}



		.data-chart {
			background-color: white;
			box-shadow: 0 4rpx 10rpx rgba(0, 0, 0, 0.5);
			border-radius: 5%;
			margin-left: 5%;
			width: 90%;
			height: 30vh;
			margin-top: 5%;
		}
	}
</style>