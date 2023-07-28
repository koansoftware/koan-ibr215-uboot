if [ "$1" = "ibr215" ]; then
    project="ibr215"
elif [ "$1" = "hx100-smc" ]; then
    project="hx100-smc"
elif [ "$1" = "rp103-smc" ]; then
    project="rp103-smc"
elif [ "$1" = "TVMB" ]; then
    project="TVMB"
else
   echo "not surppose project"
    project="TVMB"
#exit;
fi

source /opt/fsl-imx-wayland/5.4-zeus/environment-setup-aarch64-poky-linux 

if [ "$project" = "hx100-smc" ]; then
PRODUCT_CONFIG=imx8mp_evk_hx100_smc_defconfig
elif [ "$project" = "rp103-smc" ]; then
PRODUCT_CONFIG=imx8mp_evk_rp103_smc_defconfig
elif [ "$project" = "TVMB" ]; then
PRODUCT_CONFIG=imx8mp_ddr4_hms_tvmb_defconfig
else
PRODUCT_CONFIG=imx8mp_evk_defconfig
fi

cp ../imx-mkimage/iMX8M/lpddr4_pmu_train_1d_dmem_202006.bin lpddr4_pmu_train_1d_dmem.bin
cp ../imx-mkimage/iMX8M/lpddr4_pmu_train_1d_imem_202006.bin lpddr4_pmu_train_1d_imem.bin
cp ../imx-mkimage/iMX8M/lpddr4_pmu_train_2d_dmem_202006.bin lpddr4_pmu_train_2d_dmem.bin
cp ../imx-mkimage/iMX8M/lpddr4_pmu_train_2d_imem_202006.bin lpddr4_pmu_train_2d_imem.bin
make $PRODUCT_CONFIG

make -j8

cp -avf spl/u-boot-spl.bin ../imx-mkimage/iMX8M/
cp -avf u-boot-nodtb.bin ../imx-mkimage/iMX8M/
if [ "$project" = "hx100-smc" ]; then
	cp -avf arch/arm/dts/imx8mp-evk-hx100-smc.dtb ../imx-mkimage/iMX8M/imx8mp-evk.dtb
elif [ "$project" = "TVMB" ]; then
	cp -avf arch/arm/dts/imx8mp-ddr4-hms-tvmb.dtb ../imx-mkimage/iMX8M/imx8mp-ddr4-evk.dtb
else
	cp -avf arch/arm/dts/imx8mp-evk.dtb ../imx-mkimage/iMX8M/
fi


#cd ../imx-mkimage
#if [ "$project" = "TVMB" ]; then
#./build.sh TVMB
#else
#./build.sh 
#fi
#cd -
