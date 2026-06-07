<template>
	<view class="main">
		<view class="title">
			<view class="img-box">
				<image src="../static/logo.png" mode="" class="logo"></image>
				<view class="word">
					智洁环控
				</view>
			</view>
			<view class="button" @click="openBin">
				一键开盖
			</view>
		</view>
		<view class="all-choose">
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
			<view class="title-main">
				数据检测
			</view>
			<view class="button" @click="toMap">
				查看地图
			</view>
		</view>
		<view class="warn">
			当气体和烟雾浓度高于150标准值系统自动报警
		</view>
		<view class="littleTitle">
			甲烷检测
		</view>
		<view class="carbon-chart">
			<qiun-data-charts type="line" :opts="carbonOpts" :chartData="carbonChartData" :optsWatch="false" />
		</view>
		<view class="littleTitle">
			烟雾检测
		</view>
		<view class="smoke-chart">
			<qiun-data-charts type="line" :opts="smokeOpts" :chartData="smokeChartData" :optsWatch="false" />
		</view>
		<view class="mask-box" v-if="warnShow">
			<view class="warn-big">
				<MapVue class="map"></MapVue>

				<view class="word">
					位于天津理工大学集群的05号垃圾桶甲烷量超标
				</view>
				<view class="word">
					有自燃隐患，请前往查看！
				</view>
				<view class="button-box">
					<view class="button" @click="disappear">
						知道了
					</view>
				</view>
			</view>
		</view>

	</view>

</template>

<script setup lang="ts">
	import { ref, watch } from 'vue';
	import MapVue from './Map.vue';
	const array = ref(['1号桶', '2号桶', '3号桶', '4号桶'])
	const index = ref(0);
	const options = ref();
	const warnShow = ref(false);
	const token = uni.getStorageSync('token');
	let cluster_id = uni.getStorageSync('clusterId');
	const bin_id = ref(1);
	const bindPickerChange = function (e) {
		index.value = e.detail.value;
		bin_id.value = options.value[index.value].binId;
	};
	let carbonChartData = ref({})
	const carbonOpts = {
		color: ["#405b14", "#FC8452", "#9A60B4", "#ea7ccc"],
		padding: [15, 10, 0, 15],
		enableScroll: false,
		legend: {},
		xAxis: {
			disableGrid: true
		},
		yAxis: {
			gridType: "dash",
			dashLength: 2,
			data: [
				{
					min: 0,
					max: 260,
				}
			]
		},
		extra: {
			line: {
				type: "straight",
				width: 2,
				activeType: "hollow"
			}
		}
	}
	let carbonRes = {
		categories: ["", "", "", "", ""],
		series: [
			{
				name: "甲烷浓度",
				data: []
			}
		]
	};
	carbonChartData.value = JSON.parse(JSON.stringify(carbonRes));
	let smokeChartData = ref({})
	const smokeOpts = {
		color: ["#405b14", "#91CB74", "#FAC858", "#EE6666", "#73C0DE", "#3CA272", "#FC8452", "#9A60B4", "#ea7ccc"],
		padding: [15, 10, 0, 15],
		enableScroll: false,
		legend: {},
		xAxis: {
			disableGrid: true
		},
		yAxis: {
			gridType: "dash",
			dashLength: 2,
			data: [
				{
					min: 0,
					max: 260,
				}
			]
		},
		extra: {
			line: {
				type: "straight",
				width: 2,
				activeType: "hollow"
			}
		}
	}
	let smokeRes = {
		categories: ["", "", "", "", ""],
		series: [
			{
				name: "烟雾浓度",
				data: []
			}
		]
	};
	smokeChartData.value = JSON.parse(JSON.stringify(smokeRes));
	async function getBin() {
		cluster_id = uni.getStorageSync('clusterId')
		uni.request({
			url: `https://trash.sipc115.com/api/data/cluster/${cluster_id}/bin`,
			method: 'GET',
			header: {
				'Authorization': token,
			},
			success: (res) => {
				console.log(res.data);
				options.value = res.data.data;
				for (let i = 0; i < options.value.length; i++) {
					array.value[i] = res.data.data[i].binName;
				}

			}
		});
	}
	getBin()
	async function getJwTimes() {
		uni.request({
			url: `https://trash.sipc115.com/api/data/bin/${bin_id.value}/methane`,
			method: 'GET',
			header: {
				'Authorization': token,
			},
			success: (response) => {
				console.log(response.data);

				carbonRes.series[0].data = response.data.data.value;

				carbonChartData.value = JSON.parse(JSON.stringify(carbonRes));
			}
		});
	}

	getJwTimes()
	async function getSmokeTimes() {
		uni.request({
			url: `https://trash.sipc115.com/api/data/bin/${bin_id.value}/smog`,
			method: 'GET',
			header: {
				'Authorization': token,
			},
			success: (response) => {
				console.log(response.data);

				smokeRes.series[0].data = response.data.data.value;

				smokeChartData.value = JSON.parse(JSON.stringify(smokeRes));
			}
		});
	}

	getSmokeTimes()
	async function getJwTimesAgain() {
		uni.request({
			url: `https://trash.sipc115.com/api/data/bin/${bin_id.value}/methane`,
			method: 'GET',
			header: {
				'Authorization': token,
			},
			success: (response) => {
				console.log(response.data);

				for (let i = 0; i < 4; i++) {
					carbonRes.series[0].data[i] = carbonRes.series[0].data[i + 1];
				}
				carbonRes.series[0].data[4] = response.data.data.value[4];
				carbonChartData.value = JSON.parse(JSON.stringify(carbonRes));

				if (carbonRes.series[0].data[4] > 150) {
					warnShow.value = true;
				}
			}
		});
	}
	async function getSmokeTimesAgain() {
		uni.request({
			url: `https://trash.sipc115.com/api/data/bin/${bin_id.value}/smog`,
			method: 'GET',
			header: {
				'Authorization': token,
			},
			success: (response) => {
				console.log(response.data);
				for (let i = 0; i < 4; i++) {
					smokeRes.series[0].data[i] = smokeRes.series[0].data[i + 1];
				}
				smokeRes.series[0].data[4] = response.data.data.value[4];
				if (smokeRes.series[0].data[4] > 150) {
					warnShow.value = true;
				}
				smokeChartData.value = JSON.parse(JSON.stringify(smokeRes));
			}
		});
	}
	async function openBin() {
		uni.request({
			url: `https://trash.sipc115.com/api/control/open/${bin_id.value}`,
			method: 'GET',
			header: {
				'Authorization': token,
			},
			success: (res) => {
				console.log(res.data);
			}
		});
	}
	function toMap() {
		uni.navigateTo({
			url: '/pages/MapShow'
		})
	}
	function disappear() {
		warnShow.value = false;
	}
	watch(bin_id, () => {
		getJwTimes()
		getSmokeTimes()
	})
	setInterval(() => {
		getJwTimesAgain()
		getSmokeTimesAgain()
	}, 1000 * 10)
</script>

<style scoped lang="scss">
	.main {
		width: 100vw;
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

			.warn-big {
				position: absolute;
				top: 50%;
				left: 50%;
				transform: translate(-50%, -50%);
				background-color: white;
				width: 90%;
				height: 70%;
				border-radius: 15px;

				.map {
					width: 95%;
					margin-left: 2.5%;
					height: 650rpx;
				}



				.word {
					margin-top: 1%;
					display: flex;
					justify-content: center;
					color: rgba(223, 12, 12, 1);
					font-size: 28rpx;
					font-weight: bold;
				}


				.button-box {
					margin-top: 5%;
					width: 100%;
					display: flex;
					align-items: center;
					justify-content: center;

					.button {
						display: flex;
						align-items: center;
						border-radius: 5px;
						justify-content: center;
						font-size: 35rpx;
						width: 20%;
						font-weight: bold;
						color: white;
						background-color: rgba(233, 17, 17, 0.55);
					}
				}

			}
		}


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

			.button {
				height: 100%;
				width: 33%;
				font-size: 35rpx;
				font-weight: bold;
				color: white;
				display: flex;
				align-items: center;
				justify-content: center;
				border-radius: 5px;
				background-color: rgb(86, 119, 34);
				margin-right: 5%;
			}
		}

		.all-choose {
			display: flex;
			margin-top: 5%;
			align-items: center;

			.title-main {
				font-weight: bold;
				font-size: 45rpx;
				display: flex;
				justify-content: center;
				width: 25%;
				margin-left: 7.5%;

			}

			.group-choose {
				font-weight: bold;
				width: 25%;
				margin-left: 5%;
				height: 50rpx !important;
				font-size: 20rpx;
				border-radius: 5px;
				display: flex;
				justify-content: center;
				align-items: center;
				background-color: white;
			}

			.button {
				height: 100%;
				width: 22%;
				font-size: 35rpx;
				font-weight: bold;
				color: white;
				display: flex;
				align-items: center;
				justify-content: center;
				border-radius: 5px;
				background-color: rgb(86, 119, 34);
				margin-left: 10%;
			}
		}


		.warn {
			margin-top: 3%;
			color: rgba(223, 12, 12, 1);
			font-size: 20rpx;
			display: flex;
			justify-content: center;
		}

		.littleTitle {
			margin-top: 5%;
			font-size: 32rpx;
			display: flex;
			justify-content: center;
			font-weight: bold;
		}

		.carbon-chart {
			margin-left: 5%;
			width: 90%;
			height: 40vh;
		}

		.smoke-chart {
			margin-left: 5%;
			width: 90%;
			height: 40vh;
		}
	}
</style>