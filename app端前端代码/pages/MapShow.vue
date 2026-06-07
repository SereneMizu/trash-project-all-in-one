<template>
	<view class="main">
		<view class="title">
			地图
		</view>
		<MapVue class="map"></MapVue>
		<view class="path">
			<view class="text-start">
				从
			</view>
			<input type="text" class="input-start" placeholder="请输入桶编号" />
			<view class="text-end">
				到
			</view>
			<input type="text" class="input-end" placeholder="请输入桶编号" />
		</view>
		<view class="query-button">
			<button class="button">查询</button>
		</view>
	</view>

</template>

<script setup lang="ts">
	import MapVue from './Map.vue';
</script>

<style scoped lang="scss">
	.main {
		width: 100vw;
		height: 100vh;
		background-color: rgba(228, 246, 200, 0.61);
		margin: 0;
		padding: 0;

		.title {
			display: flex;
			justify-content: center;
			font-size: 45rpx;
			font-weight: bold;
			padding-top: 5%;
		}

		.map {
			margin-top: 10%;
			height: 300px;
		}

		.path {
			display: flex;
			align-items: center;

			.text-start {
				margin-left: 10%;
			}

			.input-start {
				width: 30%;
				margin-left: 3%;
				border-bottom: 1rpx solid;
			}

			.text-end {
				margin-left: 5%;
			}

			.input-end {
				width: 30%;
				margin-left: 3%;
				border-bottom: 1rpx solid;
			}
		}

		.query-button {
			width: 50%;
			margin-left: 25%;
			height: 80rpx;
			margin-top: 10%;

			.button {
				height: 100%;
				width: 40%;
				font-size: 35rpx;
				font-weight: bold;
				color: white;
				display: flex;
				align-items: center;
				justify-content: center;
				background-color: rgb(86, 119, 34);
			}
		}
	}
</style>